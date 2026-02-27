template<int _MOD>
struct Modint{
    static int mod;
    int v;

    static int getMod() {
        if (_MOD != 0) return _MOD;
        return mod;
    }

    static void setMod(int m) {
        mod = m;
    }

    Modint() : v(0) {}
    Modint(long long _v) {
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

    Modint pow(long long k) const {
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
        return stream >> other.v;
    } 

    friend ostream& operator << (ostream &stream, const Modint &other) {
        return stream << other.v;
    }
};

template<>
int Modint<0>::mod = 1;