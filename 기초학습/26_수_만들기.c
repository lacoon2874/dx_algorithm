#include<iostream>

using namespace std;

struct Element {
    int count;
    int remain;

    bool operator<(const Element& e) const {
        return this->count < e.count;
    }

    bool operator>(const Element& e) const {
        return this->count > e.count;
    }
};

class Heap {
    Element array[200000];
    int index;

public:
    void init() {
        index = 0;
    }

    void push(int count, int remain) {
        int cur = ++index;
        array[cur].count = count;
        array[cur].remain = remain;

        while (cur != 1) {
            if (array[cur] > array[cur / 2]) {
                break;
            }
            swap(array[cur], array[cur / 2]);
            cur /= 2;
        }
    }

    Element pop() {
        Element retVal = array[1];
        swap(array[1], array[index--]);

        int parent = 1, child = 2;
        while (child <= index) {
            if (child + 1 <= index && array[child + 1] < array[child]) {
                child++;
            }
            if (array[parent] < array[child]) {
                break;
            }
            swap(array[parent], array[child]);
            parent = child;
            child *= 2;
        }

        return retVal;
    }

    bool empty() {
        return (index <= 0 ? true : false);
    }
};

Heap heap;

int main(int argc, char** argv)
{
    int test_case;
    int T;
    int a[10];

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n, k;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cin >> k;

        heap.init();
        heap.push(0, k);
        int answer;
        while (!heap.empty()) {
            Element cur = heap.pop();
            if (cur.remain == 0) {
                answer = cur.count;
                break;
            }
            heap.push(cur.count + cur.remain, 0);
            for (int i = 0; i < n; i++) {
                heap.push(cur.count + cur.remain % a[i], cur.remain / a[i]);
            }
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}