#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int main(int argc, char** argv)
{
    int test_case;
    int T;
    char array[300][300];

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n, answer = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> array[i][j];
            }
        }
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (array[r][c] != '*') {
                    int count = 0;
                    for (int i = r - 1; i <= r + 1; i++) {
                        if (i >= 0 && i < n) {
                            for (int j = c - 1; j <= c + 1; j++) {
                                if (j >= 0 && j < n && array[i][j] == '*') {
                                    count++;
                                }
                            }
                        }
                    }
                    array[r][c] = '0' + count;
                }
            }
        }

        queue<pair<int, int>> Q;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (array[r][c] == '0') {
                    answer++;
                    Q.emplace(r, c);
                    array[r][c] = '9';
                    while (!Q.empty()) {
                        int curRow = Q.front().first;
                        int curCol = Q.front().second;
                        Q.pop();
                        for (int i = curRow - 1; i <= curRow + 1; i++) {
                            if (i >= 0 && i < n) {
                                for (int j = curCol - 1; j <= curCol + 1; j++) {
                                    if (j >= 0 && j < n) {
                                        if (array[i][j] == '0') {
                                            Q.emplace(i, j);
                                        }
                                        array[i][j] = '9';
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (array[r][c] >= '0' && array[r][c] <= '8') {
                    answer++;
                }
            }
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}