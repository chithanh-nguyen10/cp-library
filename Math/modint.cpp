template<int64_t _MOD>
struct Modint{
    static int64_t mod;
    int64_t v;

    static int64_t getMod() {
        if (_MOD != 0) return _MOD;
        return mod;
    }

    static void setMod(int64_t m) {
        mod = m;
    }

    Modint() : v(0) {}
    Modint(int64_t _v) {
        v = _v % getMod();
        if (v < 0) v += getMod();
    }

    Modint& operator += (const Modint &other) {
        v += other.v;
        if (v >= getMod()) v -= getMod();
        return *this;
    }

    Modint& operator -= (const Modint &other) {
        v -= other.v;
        if (v < 0) v += getMod();
        return *this;
    }

    Modint& operator *= (const Modint &other) {
        v = 1ll * v * other.v % getMod();
        return *this;
    }

    Modint pow(int64_t k) const {
        Modint res(1), base = *this;
        while (k) {
            if (k & 1) res *= base;
            base *= base;
            k >>= 1;
        }

        return res;
    }

    Modint inv() const {return pow(getMod() - 2);}

    Modint& operator /= (const Modint &other) {
        *this *= other.inv();
        return *this;
    }

    friend Modint operator + (Modint a, const Modint &b) {return a += b;}
    friend Modint operator - (Modint a, const Modint &b) {return a -= b;}
    friend Modint operator * (Modint a, const Modint &b) {return a *= b;}
    friend Modint operator / (Modint a, const Modint &b) {return a /= b;}

    Modint operator - () const {return Modint(0) - *this;}

    bool operator == (const Modint &t) const {return v == t.v;}
    bool operator != (const Modint &t) const {return v != t.v;}
    bool operator < (const Modint &t) const {return v < t.v;}

    friend istream& operator >> (istream &stream, Modint &other) {
        int64_t inp; stream >> inp;
        other = Modint(inp);
        return stream;
    } 

    friend ostream& operator << (ostream &stream, const Modint &other) {
        return stream << other.v;
    }

    // Long long casting
    operator int64_t() const {return v;} 
};

template<>
int64_t Modint<0>::mod = 1;