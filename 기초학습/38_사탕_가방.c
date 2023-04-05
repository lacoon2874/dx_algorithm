#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;
    long long arr[100];

    for (test_case = 1; test_case <= T; ++test_case)
    {
        long long n, m;
        cin >> n >> m;

        long long end = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            if (arr[i] > end) {
                end = arr[i];
            }
        }
        long long start = 1, answer = 0;
        while (start <= end) {
            long long mid = start + (end - start) / 2;
            long long remain = m;
            for (int i = 0; i < n; i++) {
                remain -= (arr[i] / mid);
            }
            remain <= 0 ? answer = mid, start = mid + 1 : end = mid - 1;
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}