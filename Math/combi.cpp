// Name: Combinatorics (based on jiangly's template)

// Warning!!!: Z must be Modint
template<class Z>
struct Comb {
    int n;
    vector<Z> fact, ifact;

    Comb() : n(0), fact{1}, ifact{1} {}
    Comb(int _n) : Comb() {
        init(_n);
    }

    void init(int m) {
        m = min((int64_t)m, Z::getMod() - 1);
        if (m <= n) return;
        fact.resize(m + 1);
        ifact.resize(m + 1);

        for (int i = n + 1; i <= m; ++i)
            fact[i] = fact[i - 1] * Z(i);
        
        ifact[m] = fact[m].inv();
        for (int i = m; i > n; --i)
            ifact[i - 1] = ifact[i] * Z(i);
        
        n = m;
    }

    Z fac(int m) {
        if (m > n) init(2 * m);
        return fact[m];
    }

    Z invfac(int m) {
        if (m > n) init(2 * m);
        return ifact[m];
    }

    // n choose m
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
};