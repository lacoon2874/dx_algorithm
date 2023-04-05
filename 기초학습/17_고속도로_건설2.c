#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Element {
    int start;
    int end;
    int cost;

    Element(int s, int e, int c) : start(s), end(e), cost(c) {}

    bool operator<(const Element& e) const {
        return this->cost > e.cost;
    }
};

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n, m;
        cin >> n >> m;
        int parent[50001];

        priority_queue<Element> pq;
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        int s, e, c;
        for (int i = 0; i < m; i++) {
            cin >> s >> e >> c;
            pq.emplace(s, e, c);
        }

        int count = 1, answer = 0;
        stack<int> stk;
        while (count < n) {
            Element cur = pq.top();
            pq.pop();

            int a = cur.start;
            for (; a != parent[a]; a = parent[a]) {
                stk.push(a);
            }
            while (!stk.empty()) {
                parent[stk.top()] = a;
                stk.pop();
            }
            int b = cur.end;
            for (; b != parent[b]; b = parent[b]) {
                stk.push(b);
            }
            while (!stk.empty()) {
                parent[stk.top()] = b;
                stk.pop();
            }

            if (a != b) {
                parent[b] = a;
                count++;
                answer += cur.cost;
            }
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}