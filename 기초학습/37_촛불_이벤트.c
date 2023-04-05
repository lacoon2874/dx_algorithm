#include<iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        long long n;
        cin >> n;
        n *= 2;
        long long temp = static_cast<long long>(sqrt(n));

        cout << '#' << test_case << ' ';
        if (temp * (temp + 1) == n) {
            cout << temp << '\n';
        }
        else {
            cout << "-1\n";
        }
    }

    return 0;
}