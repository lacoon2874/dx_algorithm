#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        int count = 1, n, cur;
        cin >> n;
        unsigned int check = 0u, fin = (1u << 10) - 1;
        for (cur = n; true; cur += n) {
            int temp = cur;
            while (temp) {
                check |= (1u << (temp % 10));
                temp /= 10;
            }
            if ((check ^ fin) == 0) {
                break;
            }
        }
        cout << '#' << test_case << ' ' << cur << endl;
    }
    return 0;
}