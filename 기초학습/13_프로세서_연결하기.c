#include <iostream>
#include <stack>
#include <vector>
#include <utility>

using namespace std;

int main(int argc, char** argv)
{
    int test_case;
    int T;
    int array[12][12];

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n;
        cin >> n;

        vector<pair<int, int>> core;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> array[i][j];
            }
        }
        for (int i = 1; i < n - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (array[i][j]) {
                    core.emplace_back(i, j);
                }
            }
        }

        int index = 0, dir = 0, size = static_cast<int>(core.size()), r, c;
        int min_len = 1000, max_count = 0, sum = 0, count = 0;
        stack<pair<int, int>> stk;
        bool loop = true;
        while (loop) {
            if (index == size) {
                if (count > max_count || (count == max_count && sum < min_len)) {
                    max_count = count;
                    min_len = sum;
                }
                dir = 5;
            }
            else {
                r = core[index].first;
                c = core[index].second;
            }
            int i;
            switch (dir) {
            case 0:
                for (i = c + 1; i < n; i++) {
                    if (array[r][i]) {
                        break;
                    }
                }
                if (i == n) {
                    for (i = c + 1; i < n; i++) {
                        array[r][i] = 1;
                    }
                    sum += (n - c - 1);
                    count++;
                    stk.emplace(index, dir);
                    index++;
                    dir = 0;
                }
                else {
                    dir++;
                }
                break;
            case 1:
                for (i = r + 1; i < n; i++) {
                    if (array[i][c]) {
                        break;
                    }
                }
                if (i == n) {
                    for (i = r + 1; i < n; i++) {
                        array[i][c] = 1;
                    }
                    sum += (n - r - 1);
                    count++;
                    stk.emplace(index, dir);
                    index++;
                    dir = 0;
                }
                else {
                    dir++;
                }
                break;
            case 2:
                for (i = c - 1; i >= 0; i--) {
                    if (array[r][i]) {
                        break;
                    }
                }
                if (i < 0) {
                    for (i = c - 1; i >= 0; i--) {
                        array[r][i] = 1;
                    }
                    sum += c;
                    count++;
                    stk.emplace(index, dir);
                    index++;
                    dir = 0;
                }
                else {
                    dir++;
                }
                break;
            case 3:
                for (i = r - 1; i >= 0; i--) {
                    if (array[i][c]) {
                        break;
                    }
                }
                if (i < 0) {
                    for (i = r - 1; i >= 0; i--) {
                        array[i][c] = 1;
                    }
                    sum += r;
                    count++;
                    stk.emplace(index, dir);
                    index++;
                    dir = 0;
                }
                else {
                    dir++;
                }
                break;
            case 4:
                stk.emplace(index, dir);
                index++;
                dir = 0;
                break;
            default:
                if (stk.empty()) {
                    loop = false;
                }
                else {
                    index = stk.top().first;
                    dir = stk.top().second;
                    stk.pop();
                    r = core[index].first;
                    c = core[index].second;
                    switch (dir) {
                    case 0:
                        for (i = c + 1; i < n; i++) {
                            array[r][i] = 0;
                        }
                        sum -= (n - c - 1);
                        count--;
                        break;
                    case 1:
                        for (i = r + 1; i < n; i++) {
                            array[i][c] = 0;
                        }
                        sum -= (n - r - 1);
                        count--;
                        break;
                    case 2:
                        for (i = c - 1; i >= 0; i--) {
                            array[r][i] = 0;
                        }
                        sum -= c;
                        count--;
                        break;
                    case 3:
                        for (i = r - 1; i >= 0; i--) {
                            array[i][c] = 0;
                        }
                        sum -= r;
                        count--;
                        break;
                    }
                    dir++;
                }
            }
        }

        cout << '#' << test_case << ' ' << min_len << endl;
    }

    return 0;
}