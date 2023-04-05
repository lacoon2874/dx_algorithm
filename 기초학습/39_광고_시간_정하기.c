#include<iostream>

using namespace std;

int startTime[100000], endTime[100000];

int main(int argc, char** argv)
{
    int test_case;
    int T;

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int l, n;
        cin >> l >> n;
        for (int i = 0; i < n; i++) {
            cin >> startTime[i] >> endTime[i];
        }
        int cur = endTime[0] - startTime[0], left = 0, right = 0, answer = 0;
        while (left < n && right < n) {
            if (endTime[right] - startTime[left] >= l) {
                int temp = cur - (endTime[right] - startTime[left] - l);
                if (temp > answer) {
                    answer = temp;
                }
                cur -= (endTime[left] - startTime[left]);
                left++;
            }
            else {
                if (cur > answer) {
                    answer = cur;
                }
                right++;
                if (right < n) {
                    cur += (endTime[right] - startTime[right]);
                }
            }
        }
        right = n - 1;
        while (left < n) {
            if (endTime[right] - startTime[left] >= l) {
                int temp = cur - (endTime[right] - startTime[left] - l);
                if (temp > answer) {
                    answer = temp;
                }
            }
            else if (cur > answer) {
                answer = cur;
            }
            cur -= (endTime[left] - startTime[left]);
            left++;
        }

        cout << '#' << test_case << ' ' << answer << '\n';
    }

    return 0;
}