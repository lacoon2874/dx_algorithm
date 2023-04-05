#include <cstring>
#include <queue>

struct List {
    int data;
    int cost;
    List* next;
};

struct Node {
    int data;
    Node* lchild;
    Node* rchild;
    int index;
};

struct Element {
    int data;
    int index;

    Element(int d, int i) : data(d), index(i) {}

    bool operator<(const Element& e) const {
        return this->data > e.data;
    }
};

Node node_pool[600];
Node* root;
List list_pool[1450];
List* list[600];
int nodeCount, listCount;
int dist[600][600];

int getIndex(int num) {
    Node* before = nullptr;
    bool left;
    for (Node* cur = root; cur;) {
        if (num == cur->data) {
            return cur->index;
        }
        before = cur;
        if (num < cur->data) {
            cur = cur->lchild;
            left = true;
        }
        else {
            cur = cur->rchild;
            left = false;
        }
    }

    int cur = nodeCount++;
    node_pool[cur].data = num;
    node_pool[cur].lchild = nullptr;
    node_pool[cur].rchild = nullptr;
    node_pool[cur].index = cur;
    if (!before) {
        root = &node_pool[cur];
    }
    else {
        if (left) {
            before->lchild = &node_pool[cur];
        }
        else {
            before->rchild = &node_pool[cur];
        }
    }

    return cur;
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
    root = nullptr;
    nodeCount = 0;
    listCount = 0;
    for (int i = 0; i < 600; i++) {
        list[i] = nullptr;
    }
    for (int i = 0; i < N; i++) {
        int a = getIndex(sCity[i]);
        int b = getIndex(eCity[i]);

        list_pool[listCount].data = b;
        list_pool[listCount].cost = mCost[i];
        list_pool[listCount].next = list[a];
        list[a] = &list_pool[listCount++];
    }

    for (int i = 0; i < nodeCount; i++) {
        bool visit[600];
        for (int j = 0; j < nodeCount; j++) {
            dist[i][j] = 1 << 30;
            visit[j] = false;
        }
        dist[i][i] = 0;
        std::priority_queue<Element> pq;
        pq.emplace(0, i);
        while (!pq.empty()) {
            Element cur = pq.top();
            pq.pop();
            if (!visit[cur.index]) {
                visit[cur.index] = true;
                for (List* ptr = list[cur.index]; ptr; ptr = ptr->next) {
                    if (!visit[ptr->data] && cur.data + ptr->cost < dist[i][ptr->data]) {
                        dist[i][ptr->data] = cur.data + ptr->cost;
                        pq.emplace(dist[i][ptr->data], ptr->data);
                    }
                }
            }
        }
    }

    return nodeCount;
}

void add(int sCity, int eCity, int mCost) {
    int a = getIndex(sCity);
    int b = getIndex(eCity);

    list_pool[listCount].data = b;
    list_pool[listCount].cost = mCost;
    list_pool[listCount].next = list[a];
    list[a] = &list_pool[listCount++];

    bool visit[600];
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            visit[j] = false;
        }
        std::priority_queue<Element> pq;
        pq.emplace(dist[i][a], a);
        while (!pq.empty()) {
            Element cur = pq.top();
            pq.pop();
            if (!visit[cur.index]) {
                for (List* ptr = list[cur.index]; ptr; ptr = ptr->next) {
                    if (!visit[ptr->data] && cur.data + ptr->cost < dist[i][ptr->data]) {
                        dist[i][ptr->data] = cur.data + ptr->cost;
                        pq.emplace(dist[i][ptr->data], ptr->data);
                    }
                }
            }
        }
    }
}

int cost(int mHub) {
    int sum = 0, hub = getIndex(mHub);

    for (int i = 0; i < nodeCount; i++) {
        sum += dist[hub][i];
        sum += dist[i][hub];
    }

    return sum;
}