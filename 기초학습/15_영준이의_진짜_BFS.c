#include <iostream>
#include <queue>

#define MAX 10

using namespace std;

vector<int> node[100001];
int parent[100001][MAX], level[100001];

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n;
        cin >> n;
        node[1].clear();
        parent[1][0] = 0;
        level[1] = 0;
        for (int i = 2; i <= n; i++) {
            node[i].clear();
            int p;
            cin >> p;
            node[p].push_back(i);
            parent[i][0] = p;
            level[i] = level[p] + 1;
        }
        for (int i = 0; i < MAX; i++) {
            parent[0][i] = 0;
        }
        for (int i = 1; i < MAX; i++) {
            for (int j = 1; j <= n; j++) {
                parent[j][i] = parent[parent[j][i - 1]][i - 1];
            }
        }

        queue<int> Q, bfs;
        Q.push(1);
        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            bfs.push(cur);
            for (int i = 0; i < static_cast<int>(node[cur].size()); i++) {
                Q.push(node[cur][i]);
            }
        }

        long long answer = 0;
        int prev = bfs.front();
        bfs.pop();
        while (!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop();

            int a = prev, b = cur;
            if (level[a] > level[b]) {
                int dif = level[a] - level[b];
                while (dif >= (1 << MAX)) {
                    a = parent[a][MAX - 1];
                    dif -= (1 << (MAX - 1));
                }
                for (int i = 0; dif; i++, dif >>= 1) {
                    a = parent[a][i];
                }
            }
            if (level[a] < level[b]) {
                int dif = level[b] - level[a];
                while (dif >= (1 << MAX)) {
                    b = parent[b][MAX - 1];
                    dif -= (1 << (MAX - 1));
                }
                for (int i = 0; dif; i++, dif >>= 1) {
                    b = parent[b][i];
                }
            }
            if (a != b) {
                while (parent[a][MAX - 1] != parent[b][MAX - 1]) {
                    a = parent[a][MAX - 1];
                    b = parent[b][MAX - 1];
                }
                for (int i = MAX - 2; i >= 0; i--) {
                    if (parent[a][i] != parent[b][i]) {
                        a = parent[a][i];
                        b = parent[b][i];
                    }
                }
                a = parent[a][0];
            }
            answer += (level[prev] - level[a] + level[cur] - level[a]);

            prev = cur;
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}