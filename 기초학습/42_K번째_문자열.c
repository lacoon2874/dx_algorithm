#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

class Trie {
    static constexpr size_t M = 26;
    static constexpr char OFFSET = 'a';

    struct Node {
        bool terminal;
        int child[M];

        Node() : terminal(true) {
            memset(child, -1, sizeof(int) * M);
        }
    };

    struct Element {
        int pos;
        string data;

        Element(int p, string d) : pos(p), data(d) {}
    };

    vector<Node> nodes;
    stack<Element> stk;

public:
    Trie() : nodes(1) {}

    void init() {
        nodes.resize(1);
        nodes[0] = Node();
        nodes[0].terminal = false;
        while (!stk.empty()) {
            stk.pop();
        }
        stk.emplace(0, "");
    }

    void insert(string s) {
        int cur = 0;
        for (size_t i = 0; i < s.length(); i++) {
            if (nodes[cur].child[s[i] - OFFSET] == -1) {
                nodes[cur].child[s[i] - OFFSET] = nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].child[s[i] - OFFSET];
        }
    }

    string findK(int k) {
        if (k >= static_cast<int>(nodes.size())) {
            return "none";
        }

        int count = 0;
        while (!stk.empty()) {
            Element cur = stk.top();
            stk.pop();
            if (nodes[cur.pos].terminal) {
                if (++count == k) {
                    return cur.data;
                }
            }
            for (int i = static_cast<int>(M) - 1; i >= 0; i--) {
                if (nodes[cur.pos].child[i] != -1) {
                    char ch = i + OFFSET;
                    stk.emplace(nodes[cur.pos].child[i], cur.data + ch);
                }
            }
        }
    }
};

Trie trie;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int k;
        string str;
        cin >> k >> str;
        int len = static_cast<int>(str.length());

        trie.init();
        for (size_t i = 0; i < str.length(); i++) {
            trie.insert(str.substr(i));
        }

        cout << '#' << test_case << ' ' << trie.findK(k) << endl;
    }

    return 0;
}