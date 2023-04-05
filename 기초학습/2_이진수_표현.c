#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        int n;
        unsigned int m;

        cin >> n >> m;

        cout << '#' << test_case << ' ';
        if ((((1u << n) - 1) & m) == ((1u << n) - 1)) {
            cout << "ON" << endl;
        }
        else {
            cout << "OFF" << endl;
        }
    }

    return 0;
}