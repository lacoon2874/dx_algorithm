struct Pos {
    int row;
    int col;
    int num;

    Pos(int r, int c, int n) : row(r), col(c), num(n) {}
};

struct Element {
    Pos pos;
    Element* next;

    Element(int r, int c, int n, Element* ptr) : pos(r, c, n), next(ptr) {}
};

class Queue {
    Element* front;
    Element* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() {
        while (front) {
            Element* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void push(int r, int c, int n) {
        Element* temp = new Element(r, c, n, nullptr);

        if (!front) {
            front = temp;
        }
        else {
            rear->next = temp;
        }
        rear = temp;
    }

    Pos pop() {
        Pos retVal = front->pos;
        Element* temp = front;
        front = front->next;
        delete temp;

        return retVal;
    }

    bool empty() {
        return (front ? false : true);
    }
};

int array[11][11];
bool visit[11][11];
int nSize;

void bfs_init(int map_size, int map[10][10]) {
    nSize = map_size;
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            array[i + 1][j + 1] = map[i][j];
        }
    }
}

int bfs(int x1, int y1, int x2, int y2) {
    for (int i = 1; i <= nSize; i++) {
        for (int j = 1; j <= nSize; j++) {
            visit[i][j] = false;
        }
    }
    Queue Q;
    Q.push(y1, x1, 0);
    visit[y1][x1] = true;

    int r, c, n;
    while (!Q.empty()) {
        Pos cur = Q.pop();
        r = cur.row;
        c = cur.col;
        n = cur.num;
        if (r == y2 && c == x2) {
            return n;
        }

        if (r + 1 <= nSize && array[r + 1][c] == 0 && !visit[r + 1][c]) {
            visit[r + 1][c] = true;
            Q.push(r + 1, c, n + 1);
        }
        if (c + 1 <= nSize && array[r][c + 1] == 0 && !visit[r][c + 1]) {
            visit[r][c + 1] = true;
            Q.push(r, c + 1, n + 1);
        }
        if (r - 1 > 0 && array[r - 1][c] == 0 && !visit[r - 1][c]) {
            visit[r - 1][c] = true;
            Q.push(r - 1, c, n + 1);
        }
        if (c - 1 > 0 && array[r][c - 1] == 0 && !visit[r][c - 1]) {
            visit[r][c - 1] = true;
            Q.push(r, c - 1, n + 1);
        }
    }

    return -1;
}