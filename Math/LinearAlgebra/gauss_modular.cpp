/*
Name: Gauss-Jordan elimination with modulo.
Tested:
- https://cses.fi/problemset/task/3154
*/

// Returns: number of solution (0, 1 or 2 (represent infinite))
//   When the system has at least one solution, ans will contains
//   one possible solution
// Solve:
//   sum(aij * xj) = bi (mod mod)
// last column of a is vector b
namespace GaussElimination {
    using ll = long long;
 
    ll pw(ll a, ll b, ll mod) {
        ll res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
 
    ll inv(ll a, ll mod) {
        a %= mod;
        if (a < 0) a += mod;
        return pw(a, mod - 2, mod);
    }

    int gauss(vector<vector<ll>> a, vector<ll> &ans, ll mod) {
        int n = (int)a.size();
        int m = (int)a[0].size() - 1;
 
        for (int i = 0; i < n; ++i)
            for (int j = 0; j <= m; ++j) {
                a[i][j] %= mod;
                if (a[i][j] < 0) a[i][j] += mod;
            }
 
        vector<int> where(m, -1);
 
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            int sel = row;
            while (sel < n && a[sel][col] == 0) ++sel;
            if (sel == n) continue;
 
            swap(a[sel], a[row]);
            where[col] = row;
 
            ll inv_pivot = inv(a[row][col], mod);
            for (int j = col; j <= m; ++j)
                a[row][j] = a[row][j] * inv_pivot % mod;
 
            for (int i = row + 1; i < n; ++i) {
                if (a[i][col] == 0) continue;
                ll c = a[i][col];
                for (int j = col; j <= m; ++j) {
                    a[i][j] = (a[i][j] - c * a[row][j]) % mod;
                    if (a[i][j] < 0) a[i][j] += mod;
                }
            }
 
            ++row;
        }
 
        ans.assign(m, 0);
 
        for (int i = n - 1; i >= 0; --i) {
            int pivot_col = -1;
            for (int j = 0; j < m; ++j) {
                if (a[i][j] != 0) {
                    pivot_col = j;
                    break;
                }
            }
 
            if (pivot_col == -1) {
                if (a[i][m] != 0) return 0;
                continue;
            }
 
            ll val = a[i][m];
            for (int j = pivot_col + 1; j < m; ++j) {
                val = (val - a[i][j] * ans[j]) % mod;
                if (val < 0) val += mod;
            }
            ans[pivot_col] = val;
        }
 
        for (int i = 0; i < m; ++i)
            if (where[i] == -1)
                return 2;
        return 1;
    }
}

/*
Example Usage:
const int MOD = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;
 
    vector<vector<ll>> sle(n, vector<ll>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            cin >> sle[i][j];
        }
    }
 
    vector<ll> ans;
    int roots = GaussElimination::gauss(sle, ans, MOD);
 
    if (roots == 0) {
        cout << -1;
        return;
    }
 
    for (auto v : ans)
        cout << v << ' ';
}
*/