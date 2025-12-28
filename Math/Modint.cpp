template<int _MOD>
struct Modint{
    static const int mod = _MOD;
    int v;

    Modint() : v(0) {}
    Modint(int _v) : v(_v) {}
    Modint& operator += (const Modint &other) {
        v += other.v;
        if (v >= mod) v -= mod;
        return *this;
    }

    Modint& operator -= (const Modint &other) {
        v -= other.v;
        if (v < 0) v += mod;
        return *this;
    }

    Modint& operator *= (const Modint &other) {
        v = 1ll * v * other.v % mod;
        return *this;
    }

    Modint pow(int k) const {
        Modint res(1), base = *this;
        while (k) {
            if (k & 1) res *= base;
            base *= base;
            k >>= 1;
        }

        return res;
    }

    Modint inv() const {return pow(mod - 2);}

    Modint& operator /= (const Modint &other) {
        *this *= other.inv();
        return *this;
    }

    friend Modint operator + (Modint a, const Modint &b) {return a += b;}
    friend Modint operator - (Modint a, const Modint &b) {return a -= b;}
    friend Modint operator * (Modint a, const Modint &b) {return a *= b;}
    friend Modint operator / (Modint a, const Modint &b) {return a /= b;}

    Modint operator - () const {return Modint(0) - *this;}

    friend ostream& operator << (ostream &stream, const Modint &other) {
        return stream << other.v;
    }
};