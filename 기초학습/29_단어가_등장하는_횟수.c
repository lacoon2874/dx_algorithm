#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int same[100000];

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        string a, b;
        cin >> a >> b;

        std::memset(same, 0, 100000);
        int len = static_cast<int>(b.length());
        int j = 0;
        for (int i = 1; i < len; i++) {
            while (j > 0 && b[i] != b[j]) {
                j = same[j - 1];
            }
            if (b[i] == b[j]) {
                same[i] = ++j;
            }
        }

        int i = 0, answer = 0;
        j = 0;
        while ((i - j) <= static_cast<int>(a.length()) - len) {
            for (; j < len; i++, j++) {
                if (a[i] != b[j]) {
                    break;
                }
            }
            if (j == 0) {
                i++;
                continue;
            }
            if (j == len) {
                answer++;
            }
            j = same[j - 1];
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}