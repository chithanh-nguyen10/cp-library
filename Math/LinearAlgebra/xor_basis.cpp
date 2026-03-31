/*
Name: Xor Basis (based on USACO)
Tested:
- https://cses.fi/problemset/task/3191
- https://cses.fi/problemset/task/3211
- https://codeforces.com/contest/662/problem/A
*/

struct XorBasis {
    vector<int64_t> basis;

    // Add x to basis
    void add(int64_t x) {
        x = reduce(x);
        if (x != 0) basis.push_back(x);
    }
    
    // Reduce x by the current basis
    int64_t reduce(int64_t x) {
        for (int i = 0; i < (int)basis.size(); ++i)
            x = min(x, x ^ basis[i]);
        return x;
    }

    // Return true if x is representable by current basis
    bool canRepresent(int64_t x) {
        return reduce(x) == 0;
    }
    
    // Return basis size
    int size() {
        return (int)basis.size();
    }
};