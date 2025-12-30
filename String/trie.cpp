/*
Name: Trie
Tested:
- MarisaOJ: https://marisaoj.com/problem/693
*/

const int MAXCHAR = 26;
struct Node {
    Node *child[MAXCHAR];
    int cntEnd = 0;

    Node() {
        for (int i = 0; i < MAXCHAR; ++i)
            child[i] = nullptr;
    }
};

struct Trie {
    Node root;

    Trie() {
        root = Node();
    }

    void addString(string &s) {
        Node *cur = &root;
        
        for (char c : s) {
            int nxt = c - 'a';
            if (!cur->child[nxt]) cur->child[nxt] = new Node();
            cur = cur->child[nxt];
        }

        cur->cntEnd++;
    }

    bool findString(string &s) {
        Node *cur = &root;

        for (char c : s) {
            int nxt = c - 'a';
            if (!cur->child[nxt]) return 0;
            cur = cur->child[nxt];
        }

        return (cur->cntEnd >= 1);
    }

    /*
    For other purpose
    void dfs(Node *u) {
        for (int i = 0; i < MAXCHAR; ++i) {
            if (!u->child[i]) continue;
            dfs(u->child[i]);
        }
    }
    */

    void sortStringDFS(Node* u, string cur, vector<string> &res) {
        for (int i = 1; i <= u->cntEnd; ++i) res.push_back(cur);
        for (int i = 0; i < MAXCHAR; ++i) {
            if (!u->child[i]) continue;
            char c = 'a' + i;
            sortStringDFS(u->child[i], cur + c, res);
        }
    }
 
    vector<string> sortString() {
        vector<string> res;
        sortStringDFS(&root, "", res);
        return res;
    }
};