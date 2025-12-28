/*
Tested:
- CSES 1684: https://cses.fi/problemset/task/1684
- Yosupo 2 Sat: https://judge.yosupo.jp/problem/two_sat
*/

// Indexed from 1
// Use -u to represent "not u"
// NOTE!!!!!! Call buildSCC before solve
struct TWOSAT{
    int n;
    vector<vector<int>> adj;
    vector<int> num, low, id;
    stack<int> st;
    int Time, numSCC;
 
    TWOSAT(int _n) : n(_n) {
        adj.resize(2 * n + 5, vector<int>());
        num.resize(2 * n + 5, 0);
        low.resize(2 * n + 5, 0);
        id.resize(2 * n + 5, 0);
    }
 
    int toIdx(int id) {
        if (id > 0) return id;
        else return -id + n;
    }
    
    void add_clause(int u, int v) {
        adj[toIdx(-u)].push_back(toIdx(v));
        adj[toIdx(-v)].push_back(toIdx(u));
    }
 
    void dfs(int u) {
        num[u] = ++Time;
        low[u] = num[u];
        st.push(u);
 
        for (int v : adj[u]) {
            if (num[v] == -1) continue;
            if (num[v] != 0)
                low[u] = min(low[u], num[v]);
            else {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
        }
 
        if (low[u] >= num[u]) {
            int v;
            numSCC++;
            do {
                v = st.top();
                st.pop(); num[v] = -1;
                id[v] = numSCC;
            } while(v != u);
 
        }
    }
    
    void buildSCC() {
        Time = 0; numSCC = 0;
        fill(num.begin(), num.end(), 0);
        fill(low.begin(), low.end(), 0);
        fill(id.begin(), id.end(), 0);
        while (!st.empty()) st.pop();
 
        for (int i = 1; i <= 2 * n; ++i) {
            if (num[i] == 0)
                dfs(i);
        }
    }
 
    bool solve(vector<bool> &res) {
        for (int u = 1; u <= n; ++u) {
            if (id[u] == id[toIdx(-u)]) {
                return false;
            }
        }
 
        for (int u = 1; u <= n; ++u) res[u] = (id[u] < id[toIdx(-u)]);
        return true;
    }
};