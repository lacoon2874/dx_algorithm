#include<iostream>

using namespace std;

int array[100000], temp[100000];
long long answer;

void merge(int, int, int);
void mergeSort(int, int);

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> array[i];
        }

        answer = 0;
        mergeSort(0, n - 1);

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}

void merge(int l, int m, int r) {
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (array[i] < array[j]) {
            temp[k++] = array[i++];
        }
        else {
            temp[k++] = array[j++];
            answer += (m - i + 1);
        }
    }
    while (i <= m) {
        temp[k++] = array[i++];
    }
    while (j <= r) {
        temp[k++] = array[j++];
    }
    for (k = l; k <= r; k++) {
        array[k] = temp[k];
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