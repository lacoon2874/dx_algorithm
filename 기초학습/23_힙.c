#include<iostream>

#define NODE_MAX 100000

using namespace std;

class Heap {
    int array[NODE_MAX + 1];
    int count;

public:
    void init() {
        count = 0;
    }

    void push(int data) {
        int cur = ++count;
        array[cur] = data;

        while (cur != 1) {
            if (array[cur] <= array[cur / 2]) {
                break;
            }
            swap(array[cur], array[cur / 2]);
            cur /= 2;
        }
    }

    int pop() {
        int retVal = array[1];
        swap(array[1], array[count--]);

        int parent = 1, child = 2 * parent;
        while (child <= count) {
            if (child + 1 <= count && array[child + 1] > array[child]) {
                child++;
            }
            if (array[child] <= array[parent]) {
                break;
            }
            swap(array[parent], array[child]);
            parent = child;
            child *= 2;
        }

        return retVal;
    }

    bool empty() {
        return (count <= 0 ? true : false);
    }
};

Heap heap;

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
        heap.init();
        cout << '#' << test_case << ' ';
        for (int i = 0; i < n; i++) {
            int op;
            cin >> op;
            if (op == 1) {
                int temp;
                cin >> temp;
                heap.push(temp);
            }
            else {
                if (heap.empty()) {
                    cout << "-1 ";
                }
                else {
                    cout << heap.pop() << ' ';
                }
            }
        }
        cout << '\n';
    }

    return 0;
}