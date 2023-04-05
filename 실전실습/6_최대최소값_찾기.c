class Tree {
    static constexpr int MAX_SIZE = 1 << 19;
    static constexpr int start = 1 << 18;
    static constexpr int MAX = 100000001;

    struct Node {
        int max;
        int min;
        int size;
    };

    Node node[MAX_SIZE];
    int count = 0;

    int find(int k) {
        int cur = 1;
        while (true) {
            if ((cur << 1) >= MAX_SIZE) {
                return cur;
            }
            if (node[cur << 1].size >= k) {
                cur <<= 1;
            }
            else {
                k -= node[cur << 1].size;
                cur = (cur << 1) + 1;
            }
        }
    }

public:
    void init() {
        for (int i = 1; i < MAX_SIZE; i++) {
            node[i].max = -1;
            node[i].min = MAX;
            node[i].size = 0;
        }
        count = 0;
    }

    void insert(int value) {
        int cur = start + count++;
        node[cur].max = value;
        node[cur].min = value;
        node[cur].size = 1;

        for (; cur != 1; cur >>= 1) {
            node[cur >> 1].size++;
            if (node[cur].max > node[cur >> 1].max) {
                node[cur >> 1].max = node[cur].max;
            }
            if (node[cur].min < node[cur >> 1].min) {
                node[cur >> 1].min = node[cur].min;
            }
        }
    }

    void remove(int k) {
        int cur = find(k);
        node[cur].max = -1;
        node[cur].min = MAX;
        node[cur].size = 0;

        for (; cur != 1; cur >>= 1) {
            int sibling = cur % 2 ? cur - 1 : cur + 1;
            node[cur >> 1].max = node[cur].max > node[sibling].max ? node[cur].max : node[sibling].max;
            node[cur >> 1].min = node[cur].min < node[sibling].min ? node[cur].min : node[sibling].min;
            node[cur >> 1].size--;
        }
    }

    int getDiff(int k) {
        int max = -1;
        int min = MAX;
        int cur = 1;
        while (true) {
            if (node[(cur << 1) + 1].size > k) {
                cur = (cur << 1) + 1;
            }
            else {
                max = node[(cur << 1) + 1].max > max ? node[(cur << 1) + 1].max : max;
                min = node[(cur << 1) + 1].min < min ? node[(cur << 1) + 1].min : min;
                k -= node[(cur << 1) + 1].size;

                if (node[cur << 1].size == k) {
                    max = node[cur << 1].max > max ? node[cur << 1].max : max;
                    min = node[cur << 1].min < min ? node[cur << 1].min : min;
                    k = 0;
                }
                else {
                    cur <<= 1;
                }
            }
            if (k == 0) {
                return max - min;
            }
        }
    }
};

Tree tree;

void init(int N, int mValue[30000]) {
    tree.init();
    for (int i = 0; i < N; i++) {
        tree.insert(mValue[i]);
    }
}

void add(int M, int mValue[100]) {
    for (int i = 0; i < M; i++) {
        tree.insert(mValue[i]);
    }
}

void erase(int mFrom, int mTo) {
    for (int i = mFrom; i <= mTo; i++) {
        tree.remove(mFrom);
    }
}

int find(int K) {
    return tree.getDiff(K);
}