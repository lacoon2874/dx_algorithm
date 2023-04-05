#include <iostream>
#include <string>

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

    cin >> T;

    int length[2][1001];
    int cur, prev;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        string str1, str2;
        cin >> str1 >> str2;
        int cur = 1, prev = 0;
        for (int i = 0; i <= 1000; i++) {
            length[prev][i] = 0;
        }
        for (int bIndex = 0; bIndex < static_cast<int>(str2.length()); bIndex++) {
            length[cur][0] = 0;
            for (int aIndex = 0; aIndex < static_cast<int>(str1.length()); aIndex++) {
                if (str1[aIndex] == str2[bIndex]) {
                    length[cur][aIndex + 1] = length[prev][aIndex] + 1;
                }
                else {
                    length[cur][aIndex + 1] = max(length[cur][aIndex], length[prev][aIndex + 1]);
                }
            }
            swap(cur, prev);
        }

        cout << '#' << test_case << ' ' << length[prev][static_cast<int>(str1.length())] << endl;
    }

    return 0;
}