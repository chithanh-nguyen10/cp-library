/*
Name: NearestPairPointSolver using sweepline with STL set
Tested:
- SPOJ CLOPPAIR: https://www.spoj.com/problems/CLOPPAIR/
- Yosupo: https://judge.yosupo.jp/problem/closest_pair
*/

// Use pair<int, int> to represent points
// Return the squared distance of the nearest pair of points
// Support tracing the nearest pair
// Complexity: O(n log n) with n points
// Usage:
// NearestPairPointSolver solver(points);
// Result = solver.solve()
// Warning!!!! There must be AT LEAST 2 POINTS
struct NearestPairPointSolver {
    using pii = pair<int, int>;
    int n; vector<pii> points;

    NearestPairPointSolver(vector<pii> p) {
        n = (int)p.size();
        points = p;
        ord.resize(n);
        iota(ord.begin(), ord.end(), 0);
    }

    // Returns (squared distance, (i, j)), where i and j are the indices.
    pair<long long, pii> solve() {
        assert(n >= 2);

        sort(ord.begin(), ord.end(), [&](int i, int j) {
            if (points[i].first != points[j].first) return points[i].first < points[j].first;
            return points[i].second < points[j].second;
        });

        // Handling the case of overlapping points
        for (int i = 0; i < n - 1; ++i) {
            pii p1 = points[ord[i]];
            pii p2 = points[ord[i + 1]];
            if (p1.first == p2.first && p1.second == p2.second) 
                return {0, {ord[i], ord[i + 1]}};
        }

        set<Point> st;

        long long d = sqdist(points[ord[0]], points[ord[1]]);
        pii trace = {ord[0], ord[1]};
        st.insert({points[ord[0]].first, points[ord[0]].second, ord[0]});

        int left = 0;
        for (int i = 1; i < n; ++i) {
            int id = ord[i];
            long long x = points[id].first;
            long long y = points[id].second;
    
            while (left < i && sq(x - points[ord[left]].first) > d) {
                st.erase({points[ord[left]].first, points[ord[left]].second, ord[left]});
                ++left;
            }
    
            long long sqrtd = (long long)(sqrt((long double)d)) + 1;
    
            Point lower = {x, y - sqrtd, -1};
            Point upper = {x, y + sqrtd, n};
    
            auto it1 = st.lower_bound(lower);
            auto it2 = st.upper_bound(upper);
    
            for (auto it = it1; it != it2; ++it) {
                long long cur = sq(x - it->x) + sq(y - it->y);
                if (cur < d) {
                    d = cur;
                    trace = {id, it->id};
                }
            }
    
            st.insert({x, y, id});
        }

        // For elegant purpose
        if (trace.first > trace.second)
            swap(trace.first, trace.second);

        return {d, trace};
    }

private:
    vector<int> ord;
    struct Point {
        long long x, y; int id;

        bool operator < (const Point& other) const {
            if (y != other.y) return y < other.y;
            if (x != other.x) return x < other.x;
            return id < other.id;
        }
    };

    long long sq(long long x) const {return 1ll * x * x;}
    long long sqdist(const pii &a, const pii &b) const {
        return sq(1ll * a.first - b.first) + sq(1ll * a.second - b.second);
    }
};