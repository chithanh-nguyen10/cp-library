/*
Name: Normalize
Example usage:
    Normalize norm;
    for (int i = 1; i <= n; ++i) norm.add(a[i]);
    norm.build();
    for (int i = 1; i <= n; ++i) cout << norm.compress(a[i]) << ' ';
*/

struct Normalize{
    vector<long long> vals;

    Normalize() {}

    void add(long long x) {vals.push_back(x);}
    void build() {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    int compress(long long x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    }
};