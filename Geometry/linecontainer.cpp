/*
Name: Line Container (Convex hull trick)
Tested:
- CSES 3429: https://cses.fi/problemset/task/3429
- CSES 3430: https://cses.fi/problemset/task/3430
- Yosupo: https://judge.yosupo.jp/problem/line_add_get_min
- CEOI17_BUILDING: https://oj.uz/problem/view/CEOI17_building 
*/

// O(log n) when add/query
template<bool isMin> // true for min, false for max
struct LineContainer{
    static const long long INF = LLONG_MAX;
    struct Line{
        long long a, b; // ax + b
        mutable long long p;
        bool operator < (const Line &other) const {
            if (other.a == INF && other.b == INF) return p < other.p;
            return a < other.a;
        }

        long long calc(long long x) const {return a * x + b;}
    };

    multiset<Line> hull;

    long long div(long long a, long long b) {
        return a/b - ((a ^ b) < 0 && a % b);
    }

    bool isect(typename multiset<Line>::iterator x, typename multiset<Line>::iterator y) {
        if (y == hull.end()) {x->p = INF; return 0;}
        if (x->a == y->a) x->p = (x->b > y->b ? INF : -INF);
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }

    // Add line y = ax + b
    void add(long long a, long long b) {
        if (isMin) {a = -a; b = -b;}

        auto z = hull.insert({a, b, 0}), y = z++, x = y;
		while (isect(y, z)) z = hull.erase(z);
		if (x != hull.begin() && isect(--x, y)) isect(x, y = hull.erase(y));
		while ((y = x) != hull.begin() && (--x)->p >= y->p)
			isect(x, hull.erase(y));
    }

    // Query at x
    long long query(long long x) {
        assert(!hull.empty());
        Line l = *hull.lower_bound({INF, INF, x});
        long long res = l.calc(x);
        return isMin ? -res : res;
    }
};