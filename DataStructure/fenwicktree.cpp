/*
Name: Fenwick Tree (based on jiangly's template)
Tested:
- https://cses.fi/problemset/task/1648
- https://cses.fi/problemset/task/1651
- https://oj.vnoi.info/problem/orderset (kth)
*/

// Indexed from 1
// Supports Point Update, Range Sum, Kth
// Complexity: O(log n)
template <class T>
struct FenwickTree {
    int n;
    vector<T> fen;

    FenwickTree(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        fen.resize(n + 5, T());
    }

    void update(int idx, T v) {
        for (int i = idx; i <= n; i += i & -i)
            fen[i] += v;
    }

    T get(int idx) {
        T sum = T();
        for (int i = idx; i; i -= i & -i)
            sum += fen[i];
        return sum;
    }

    T query(int l, int r) {
        return get(r) - get(l - 1);
    }

    int kth(T x) {
        int pos = 0; T sum = T();
        for (int i = __lg(n); i >= 0; --i) {
            if ((pos | (1 << i)) <= n && sum + fen[pos | (1 << i)] < x) {
                pos |= (1 << i);
                sum += fen[pos];
            }
        }

        return pos + 1;
    }
};