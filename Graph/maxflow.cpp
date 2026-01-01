struct DinicFlow{
    static const long long INF = (long long)1e18 + 7;
    int n, m;
    vector<int> dist, head, work, point, nxt;
    vector<long long> flow, capa;
 
    DinicFlow (int _n) : n(_n), m(0), dist(n + 5, 0), head(n + 5, -1), work(n + 5, 0) {
 
    }
 
    void addEdge(int u, int v, int cap) {
        point.push_back(v); capa.push_back(cap); flow.push_back(0);
        nxt.push_back(head[u]); head[u] = m++; 
        point.push_back(u); capa.push_back(0); flow.push_back(0);
        nxt.push_back(head[v]); head[v] = m++; 
    }
 
    bool bfs(int s, int t) {
        queue<int> q;
        for (int i = 1; i <= n; ++i) dist[i] = -1;
        dist[s] = 0; q.push(s);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i >= 0; i = nxt[i])
                if (flow[i] < capa[i] && dist[point[i]] < 0) {
                    dist[point[i]] = dist[u] + 1;
                    q.push(point[i]);
                }
        }
 
        return dist[t] >= 0;
    }
 
    long long dfs(int s, int t, long long f) {
        if (s == t) return f;
        for (int &i = work[s]; i >= 0; i = nxt[i]) {
            if (flow[i] < capa[i] && dist[point[i]] == dist[s] + 1) {
                long long d = dfs(point[i], t, min(f, capa[i] - flow[i]));
                if (d > 0) {
                    flow[i] += d;
                    flow[i ^ 1] -= d;
                    return d;
                }
            }
        }
 
        return 0;
    }
 
    long long maxflow(int s, int t) {
        long long res = 0;
        while (bfs(s, t)) {
            for (int i = 1; i <= n; ++i) work[i] = head[i];
            while (true) {
                int d = dfs(s, t, INF);
                if (d == 0) break;
                res += d;
            }
        }
 
        return res;
    }
};