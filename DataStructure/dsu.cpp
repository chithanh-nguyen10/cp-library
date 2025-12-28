/*
Tested:
- CSES 1676: https://cses.fi/problemset/task/1676
*/

struct DSU{
    int n;
    vector<int> par, sz;
 
    DSU(int n) : n(n), par(n + 5), sz(n + 5) {
        iota(all(par), 0);
        fill(all(sz), 1);
    }
 
    int findSet(int x) {
        return (x == par[x] ? x : par[x] = findSet(par[x]));
    }
 
    bool unite(int x, int y) {
        x = findSet(x); y = findSet(y);
        if (x == y) return 0;
        // Remove union by size if the root matters
        if (sz[x] < sz[y]) swap(x, y);
 
        sz[x] += sz[y];
        par[y] = x;
 
        return 1;
    }
 
    int size(int u) {
        return sz[findSet(u)];
    }
 
    bool same(int u, int v) {
        return findSet(u) == findSet(v);
    }
};