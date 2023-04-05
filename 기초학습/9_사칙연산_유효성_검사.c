#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
    int test_case;

    for (test_case = 1; test_case <= 10; ++test_case)
    {
        int n;
        cin >> n;
        bool answer = true;

        int a, b, c;
        char ch;

        for (int i = 1; i <= n; i++) {
            if (i * 2 + 1 <= n) {
                cin >> a >> ch >> b >> c;
                if (ch >= '0' && ch <= '9') {
                    answer = false;
                }
            }
            else if (i * 2 <= n) {
                cin >> a >> ch >> b;
                answer = false;
            }
            else {
                cin >> a >> ch;
                if (ch < '0' || ch > '9') {
                    answer = false;
                }
            }
        }

        cout << '#' << test_case << ' ' << (answer ? 1 : 0) << endl;
    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}