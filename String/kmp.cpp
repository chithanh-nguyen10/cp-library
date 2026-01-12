// Prefix function: the length of longest prefix which is also suffix

vector<int> prefix_function(string &s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }

    return pi;
}

// Example usage: List all positions at which the string t occurs in the string s
// Tested: https://oj.vnoi.info/problem/substr
/*
string s, t; cin >> s >> t;
int n = (int)s.size(), m = (int)t.size();
string concat = t + "#" + s;
vector<int> pi = prefix_function(concat);

for (int i = m + 1; i <= n + m; ++i)
    if (pi[i] == m) cout << i - 2 * m + 1 << ' ';
*/