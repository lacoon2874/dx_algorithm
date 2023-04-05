struct Node {
    int count;
    int child[5];
};

struct Stack {
    int data;
    Stack* next;

    Stack(int d, Stack* ptr) : data(d), next(ptr) {}
};

Node node[100];

void dfs_init(int N, int path[100][2])
{
    for (int i = 1; i < 100; i++) {
        node[i].count = -1;
    }
    for (int i = 0; i < N - 1; i++) {
        int a = path[i][0];
        int b = path[i][1];

        node[a].child[++node[a].count] = b;
    }
}

int dfs(int n)
{
    bool visit[100];
    for (int i = 1; i < 100; i++) {
        visit[i] = false;
    }
    Stack* top = nullptr;
    int cur = n;
    top = new Stack(cur, top);
    while (top) {
        cur = top->data;
        Stack* temp = top;
        top = top->next;
        delete temp;

        if (!visit[cur]) {
            if (cur > n) {
                while (top) {
                    temp = top;
                    top = top->next;
                    delete top;
                }

                return cur;
            }
            visit[cur] = true;
            for (int i = node[cur].count; i >= 0; i--) {
                top = new Stack(node[cur].child[i], top);
            }
        }
    }

    return -1;
}