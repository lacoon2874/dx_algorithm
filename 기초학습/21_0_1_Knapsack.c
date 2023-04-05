#include<iostream>

using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    int v[101], c[101];
    int array[2][1001];

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n, k;
        cin >> n >> k;
        int cur = 1;
        int prev = 0;
        for (int i = 1; i <= n; i++) {
            cin >> v[i] >> c[i];
        }
        for (int i = 0; i <= k; i++) {
            array[prev][i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            array[cur][0] = 0;
            for (int j = 1; j <= k; j++) {
                if (v[i] > j) {
                    array[cur][j] = array[prev][j];
                }
                else {
                    array[cur][j] = max(array[prev][j], array[prev][j - v[i]] + c[i]);
                }
            }
            swap(prev, cur);
        }

        cout << '#' << test_case << ' ' << array[prev][k] << endl;
    }

    return 0;
}