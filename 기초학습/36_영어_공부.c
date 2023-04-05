#include<iostream>

using namespace std;

int arr[200000];

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n, p;
        cin >> n >> p;

        int before, cur, answer = 0;
        cin >> before;
        arr[0] = 0;
        for (int i = 1; i < n; before = cur, i++) {
            cin >> cur;
            arr[i] = arr[i - 1] + cur - before - 1;
        }
        int start = 0, end = 0;
        while (start < n && end < n) {
            if (arr[end] - arr[start] > p) {
                if (end - start + p > answer) {
                    answer = end - start + p;
                }
                start++;
            }
            else {
                if (end - start + 1 + p > answer) {
                    answer = end - start + 1 + p;
                }
                end++;
            }
        }
        end = n - 1;
        while (start < n) {
            if (arr[end] - arr[start] > p) {
                if (end - start + p > answer) {
                    answer = end - start + p;
                }
            }
            else {
                if (end - start + 1 + p > answer) {
                    answer = end - start + 1 + p;
                }
            }
            start++;
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}