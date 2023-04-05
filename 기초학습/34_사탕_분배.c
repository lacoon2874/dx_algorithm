#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int a, b, k;
        cin >> a >> b >> k;
        long long temp = 1, n = 2, c = (a + b);
        while (k) {
            if (k & 1) {
                temp *= n;
            }
            n *= n;
            k >>= 1;
            temp %= c;
            n %= c;
        }
        temp = (temp * a) % c;
        if (temp > c / 2) {
            temp = c - temp;
        }
        cout << '#' << test_case << ' ' << temp << endl;
    }

    return 0;
}