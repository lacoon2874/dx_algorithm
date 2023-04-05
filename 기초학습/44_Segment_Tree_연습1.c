#include<iostream>

#define MAX_SIZE 1 << 18

using namespace std;

class Tree {
    static constexpr int SIZE = 1 << 18;
    static constexpr int start = 1 << 17;
    static constexpr int MAX = 1 << 30;

    struct Element {
        int min;
        int max;
    };

    Element array[SIZE];
    int count;

    int getMin(int a, int b) {
        if (a < b) {
            return a;
        }
        return b;
    }

    int getMax(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }

public:
    void init() {
        for (int i = 1; i < SIZE; i++) {
            array[i].min = MAX;
            array[i].max = -1;
        }
        count = 0;
    }

    void update(int index, int data) {
        int cur = start + index;
        array[cur].min = data;
        array[cur].max = data;
        while (cur != 1) {
            int child = cur % 2 ? cur - 1 : cur + 1;
            array[cur / 2].min = getMin(array[cur].min, array[child].min);
            array[cur / 2].max = getMax(array[cur].max, array[child].max);
            cur /= 2;
        }
    }

    void insert(int data) {
        update(count++, data);
    }

    int answer(int l, int r) {
        int min = MAX, max = -1;
        for (l += start, r += start; l != r; l >>= 1, r >>= 1) {
            if (l & 1) {
                min = getMin(array[l].min, min);
                max = getMax(array[l++].max, max);
            }
            if (r & 1) {
                min = getMin(array[--r].min, min);
                max = getMax(array[r].max, max);
            }
        }

        return max - min;
    }
};

Tree tree;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n, q;
        cin >> n >> q;
        tree.init();
        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            tree.insert(temp);
        }
        int op, a, b;
        cout << '#' << test_case << ' ';
        for (int i = 0; i < q; i++) {
            cin >> op >> a >> b;
            if (op == 0) {
                tree.update(a, b);
            }
            else {
                cout << tree.answer(a, b) << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}