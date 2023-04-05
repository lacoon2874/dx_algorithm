#include<iostream>

using namespace std;

int arr[500000], temp[500000];

void merge(int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= m) {
        temp[k++] = arr[i++];
    }
    while (j <= r) {
        temp[k++] = arr[j++];
    }
    for (k = l; k <= r; k++) {
        arr[k] = temp[k];
    }
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

int getDif(int a, int b) {
    if (a > b) {
        return a - b;
    }
    else {
        return b - a;
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
        int n, m, c1, c2;
        cin >> n >> m >> c1 >> c2;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        mergeSort(0, n - 1);

        int answer = 0, min = (1 << 30), dif = getDif(c1, c2);
        for (int i = 0; i < m; i++) {
            int cur;
            cin >> cur;
            int left = 0, right = n - 1, mid;
            while (left != right) {
                mid = left + (right - left) / 2;
                arr[mid] > cur ? right = mid : left = mid + 1;
            }
            if (arr[mid] == cur) {
                if (min != dif) {
                    min = dif;
                    answer = 0;
                }
                answer++;
            }
            else {
                if (arr[right] < cur) {
                    int sum = dif + getDif(arr[right], cur);
                    if (sum == min) {
                        answer++;
                    }
                    else if (sum < min) {
                        min = sum;
                        answer = 1;
                    }
                    if (right + 1 < n) {
                        sum = dif + getDif(arr[right + 1], cur);
                        if (sum == min) {
                            answer++;
                        }
                        else if (sum < min) {
                            min = sum;
                            answer = 1;
                        }
                    }
                }
                else {
                    int sum = dif + getDif(arr[right], cur);
                    if (sum == min) {
                        answer++;
                    }
                    else if (sum < min) {
                        min = sum;
                        answer = 1;
                    }
                    if (right - 1 >= 0) {
                        sum = dif + getDif(arr[right - 1], cur);
                        if (sum == min) {
                            answer++;
                        }
                        else if (sum < min) {
                            min = sum;
                            answer = 1;
                        }
                    }
                }
            }
        }

        cout << '#' << test_case << ' ' << min << ' ' << answer << '\n';
    }

    return 0;
}