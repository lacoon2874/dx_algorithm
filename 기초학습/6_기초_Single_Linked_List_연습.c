#define MAX_NODE 10000

struct Node {
    int data;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head = getNode(-1);
}

void addNode2Head(int data)
{
    Node* temp = getNode(data);
    temp->next = head->next;
    head->next = temp;
}

void addNode2Tail(int data)
{
    Node* search = head;
    for (; search->next; search = search->next);
    search->next = getNode(data);
}

void addNode2Num(int data, int num)
{
    Node* temp = getNode(data);
    Node* search = head;
    for (int i = 1; i < num; i++) {
        search = search->next;
    }
    temp->next = search->next;
    search->next = temp;
}

void removeNode(int data)
{
    Node* search = head;
    for (; search->next && search->next->data != data; search = search->next);
    if (search->next) {
        search->next = search->next->next;
    }
}

int getList(int output[MAX_NODE])
{
    int count = 0;
    for (Node* search = head->next; search; search = search->next) {
        output[count++] = search->data;
    }

    return count;
}