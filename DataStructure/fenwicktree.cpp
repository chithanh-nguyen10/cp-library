/*
Name: Fenwick Tree
Tested:
- CSES 1648: https://cses.fi/problemset/task/1648
- CSES 2169: https://cses.fi/problemset/task/2169
- CSES 1748: https://cses.fi/problemset/task/1748
*/

// Indexed from 1
// Supports Range Update Point Get
struct FenwickTree{
    int n, lg;
    vector<int> fen;
 
    FenwickTree() {
    }
 
    FenwickTree(int _n) : n(_n) {
        lg = __lg(n);
        fen.resize(n + 5, 0);
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

    int lower_bound(int x) {
        int pos = 0, sum = 0;
        for (int i = lg; i >= 0; --i) {
            if ((pos | (1 << i)) <= n && sum + fen[pos | (1 << i)] < x) {
                pos |= (1 << i);
                sum += fen[pos];
            }
        }

        return pos + 1;
    }
 
    int query(int l, int r) {
        return get(r) - get(l - 1);
    }
};