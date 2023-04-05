#define MAX_NODE 10000

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head, * tail;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].prev = nullptr;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head = getNode(-1);
    tail = getNode(-1);
    head->next = tail;
    tail->prev = head;
}

void addNode2Head(int data)
{
    Node* temp = getNode(data);
    temp->next = head->next;
    temp->prev = head;
    temp->next->prev = temp;
    head->next = temp;
}

void addNode2Tail(int data)
{
    Node* temp = getNode(data);
    temp->prev = tail->prev;
    temp->next = tail;
    temp->prev->next = temp;
    tail->prev = temp;
}

void addNode2Num(int data, int num)
{
    Node* temp = getNode(data);
    Node* search = head;
    for (int i = 1; i < num; i++) {
        search = search->next;
    }
    temp->next = search->next;
    temp->prev = search;
    temp->next->prev = temp;
    search->next = temp;
}

int findNode(int data)
{
    int count = 1;
    for (Node* search = head->next; search != tail && search->data != data; count++, search = search->next);

    return count;
}

void removeNode(int data)
{
    Node* search = head->next;
    for (; search != tail && search->data != data; search = search->next);
    if (search != tail) {
        search->prev->next = search->next;
        search->next->prev = search->prev;
    }
}

int getList(int output[MAX_NODE])
{
    int count = 0;
    for (Node* search = head->next; search != tail; search = search->next) {
        output[count++] = search->data;
    }

    return count;
}

int getReversedList(int output[MAX_NODE])
{
    int count = 0;
    for (Node* search = tail->prev; search != head; search = search->prev) {
        output[count++] = search->data;
    }

    return count;
}