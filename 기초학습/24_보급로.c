#include<iostream>
#include <string>

using namespace std;

struct Element {
    int row;
    int col;
    int cost;

    bool operator<(const Element& e) {
        return this->cost < e.cost;
    }

    bool operator>(const Element& e) {
        return this->cost > e.cost;
    }
};

class Heap {
    Element array[100000];
    int count;

public:
    void init() {
        count = 0;
    }

    void push(int r, int c, int n) {
        int cur = ++count;
        array[cur].row = r;
        array[cur].col = c;
        array[cur].cost = n;

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
        swap(array[1], array[count--]);

        int parent = 1, child = 2;
        while (child <= count) {
            if (child + 1 <= count && array[child + 1] < array[child]) {
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
        return (count <= 0 ? true : false);
    }
};

int map[100][100];
bool visit[100][100];
Heap heap;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    int pos[2][4] = { {1,0,-1,0}, {0,1,0,-1} };

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < n; j++) {
                map[i][j] = str[j] - '0';
                visit[i][j] = false;
            }
        }

        heap.init();
        heap.push(0, 0, 0);
        while (!heap.empty()) {
            Element cur = heap.pop();
            if (!visit[cur.row][cur.col]) {
                visit[cur.row][cur.col] = true;
                map[cur.row][cur.col] = cur.cost;
                for (int i = 0; i < 4; i++) {
                    int r = cur.row + pos[0][i];
                    int c = cur.col + pos[1][i];
                    if (r < n && r >= 0 && c < n && c >= 0 && !visit[r][c]) {
                        heap.push(r, c, cur.cost + map[r][c]);
                    }
                }
            }
        }

        cout << '#' << test_case << ' ' << map[n - 1][n - 1] << endl;
    }

    return 0;
}