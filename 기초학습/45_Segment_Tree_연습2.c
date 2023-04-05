#include<iostream>

#define MAX_SIZE 1 << 18

using namespace std;

class Tree {
    static constexpr int SIZE = 1 << 18;
    static constexpr int start = 1 << 17;
    static constexpr int MAX = 1 << 30;

    long long array[SIZE];
    int count;

public:
    void init() {
        for (int i = 1; i < SIZE; i++) {
            array[i] = 0;
        }
        count = 0;
    }

    void update(int index, long long data) {
        int cur = start + index;
        array[cur] = data;
        while (cur != 1) {
            int child = cur % 2 ? cur - 1 : cur + 1;
            array[cur / 2] = array[cur] + array[child];
            cur /= 2;
        }
    }

    void insert(long long data) {
        update(count++, data);
    }

    long long answer(int l, int r) {
        long long sum = 0;
        for (l += start, r += start; l != r; l >>= 1, r >>= 1) {
            if (l & 1) {
                sum += array[l++];
            }
            if (r & 1) {
                sum += array[--r];
            }
        }

        return sum;
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
            long long temp;
            cin >> temp;
            i % 2 ? tree.insert(-temp) : tree.insert(temp);
        }
        int op;
        cout << '#' << test_case << ' ';
        for (int i = 0; i < q; i++) {
            cin >> op;
            if (op == 0) {
                int i;
                long long x;
                cin >> i >> x;
                i % 2 ? tree.update(i, -x) : tree.update(i, x);
            }
            else {
                int l, r;
                cin >> l >> r;
                cout << (l % 2 ? -tree.answer(l, r) : tree.answer(l, r)) << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}