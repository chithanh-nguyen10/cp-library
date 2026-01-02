/*
Name: Matrix
Tested:
- Matrix Product: https://judge.yosupo.jp/problem/matrix_product
- Pow of Matrix: https://judge.yosupo.jp/problem/pow_of_matrix
*/

template<class T>
struct Matrix{
    int n, m; // numrow, numcol
    vector<vector<T>> mat;

    Matrix(int _n, int _m) : n(_n), m(_m) {
        mat.resize(n, vector<T>(m, T(0)));
    }

    Matrix (const vector<vector<T>> &vec) {
        n = (int)vec.size();
        m = (int)vec[0].size();
        mat = vec;
    }

    friend Matrix operator * (const Matrix &a, const Matrix &b) {
        assert(a.m == b.n);
        int n = a.n, m = a.m, k = b.m;
        Matrix res(n, k);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                for (int l = 0; l < k; ++l)
                    res[i][l] += a[i][j] * b[j][l];
        return res;
    }

    static Matrix identity(int x) {
        Matrix res(x, x);
        for (int i = 0; i < x; ++i) res[i][i] = T(1);
        return res;
    }

    Matrix pow(long long k) const {
        assert(n == m);
        Matrix res = identity(n), base = *this;
        while (k) {
            if (k & 1) res = res * base;
            base = base * base;
            k >>= 1;
        }

        return res;
    }

    vector<T>& operator [] (int i) {return mat[i];}
    const vector<T>& operator [] (int i) const {return mat[i];}

    friend ostream & operator << (ostream &stream, const Matrix &mat) {
        for (int i = 0; i < mat.n; ++i)
            for (int j = 0; j < mat.m; ++j)
                stream << mat[i][j] << " \n"[j == mat.m - 1];
        return stream;
    }
};