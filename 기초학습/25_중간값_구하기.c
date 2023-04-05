#include <iostream>

using namespace std;

struct Heap {
    int max[200010];
    int min[200010];
    int maxCount, minCount;

public:
    void init(int n) {
        max[1] = n;
        maxCount = 1;
        minCount = 0;
    }

    void pushMax(int data) {
        int cur = ++maxCount;
        max[cur] = data;

        while (cur != 1) {
            if (max[cur] < max[cur / 2]) {
                break;
            }
            swap(max[cur], max[cur / 2]);
            cur /= 2;
        }

        if (max[1] > min[1]) {
            swap(max[1], min[1]);

            int parent = 1, child = 2;
            while (child <= minCount) {
                if (child + 1 <= minCount && min[child + 1] < min[child]) {
                    child++;
                }
                if (min[parent] < min[child]) {
                    break;
                }
                swap(min[parent], min[child]);
                parent = child;
                child *= 2;
            }
        }
    }

    void pushMin(int data) {
        int cur = ++minCount;
        min[cur] = data;

        while (cur != 1) {
            if (min[cur] > min[cur / 2]) {
                break;
            }
            swap(min[cur], min[cur / 2]);
            cur /= 2;
        }

        if (max[1] > min[1]) {
            swap(max[1], min[1]);

            int parent = 1, child = 2;
            while (child <= maxCount) {
                if (child + 1 <= maxCount && max[child + 1] > max[child]) {
                    child++;
                }
                if (max[parent] > max[child]) {
                    break;
                }
                swap(max[parent], max[child]);
                parent = child;
                child *= 2;
            }
        }
    }

    int topMax() {
        return max[1];
    }
};

Heap heap;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n, a, x, y;
        cin >> n >> a;
        heap.init(a);
        int answer = 0;
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            heap.pushMin(x);
            heap.pushMax(y);

            answer = (answer + heap.topMax()) % 20171109;
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}