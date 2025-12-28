/*
Tested:
- CSES 1648: https://cses.fi/problemset/task/1648
- CSES 2169: https://cses.fi/problemset/task/2169
- CSES 1748: https://cses.fi/problemset/task/1748
*/

// Indexed from 1
struct FenwickTree{
    int n;
    vector<int> fen;
 
    FenwickTree() {
    }
 
    FenwickTree(int _n) : n(_n) {
        fen.resize(n + 5);
    }
 
    void update(int idx, int val) {
        for (int i = idx; i <= n; i += i & -i)
            fen[i] += val;
    }

    void updateRange(int l, int r, int val) {
        update(l, val);
        update(r + 1, -val);
    }
 
    int get(int idx) {
        int sum = 0;
        for (int i = idx; i; i -= i & -i)
            sum += fen[i];
        return sum;
    }
 
    int query(int l, int r) {
        return get(r) - get(l - 1);
    }
};