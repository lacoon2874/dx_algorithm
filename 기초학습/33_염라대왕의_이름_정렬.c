#include<iostream>
#include <string>

using namespace std;

string input[20000], temp[20000];

void merge(int l, int m, int r) {
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (input[i].length() < input[j].length() || (input[i].length() == input[j].length() && input[i].compare(input[j]) < 0)) {
            temp[k++] = input[i++];
        }
        else {
            temp[k++] = input[j++];
        }
    }
    while (i <= m) {
        temp[k++] = input[i++];
    }
    while (j <= r) {
        temp[k++] = input[j++];
    }
    for (k = l; k <= r; k++) {
        input[k] = temp[k];
    }
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

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
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> input[i];
        }
        mergeSort(0, n - 1);

        cout << '#' << test_case << '\n';
        string temp = "";
        string& before = temp;
        for (int i = 0; i < n; i++) {
            if (input[i].compare(before) != 0) {
                cout << input[i] << '\n';
            }
            before = input[i];
        }
    }

    return 0;
}