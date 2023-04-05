#include<iostream>
#define MAX_SIZE 3000

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node node[MAX_SIZE];
int nodeCnt;
Node* head, * tail;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].next = nullptr;
    node[nodeCnt].prev = nullptr;
    return &node[nodeCnt++];
}

void init() {
    nodeCnt = 0;
    head = getNode(-1);
    tail = getNode(-1);
    head->next = tail;
    tail->prev = head;
}

void addToTail(int data) {
    Node* temp = getNode(data);
    temp->prev = tail->prev;
    temp->next = tail;
    temp->prev->next = temp;
    tail->prev = temp;
}

void addToNum(int num, int data) {
    Node* temp = getNode(data);
    Node* search = head;
    for (int i = 0; i < num; i++) {
        search = search->next;
    }
    temp->next = search->next;
    temp->prev = search;
    temp->next->prev = temp;
    search->next = temp;
}

void removeAtNum(int num) {
    Node* search = head;
    for (int i = 0; i <= num; i++) {
        search = search->next;
    }
    search->next->prev = search->prev;
    search->prev->next = search->next;
}

void changeAtNum(int num, int data) {
    Node* search = head;
    for (int i = 0; i <= num; i++) {
        search = search->next;
    }
    search->data = data;
}

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        init();
        int N, M, L, num, a, b;
        cin >> N >> M >> L;

        for (int i = 0; i < N; i++) {
            cin >> num;
            addToTail(num);
        }

        char o;
        for (int i = 0; i < M; i++) {
            cin >> o;
            switch (o) {
            case 'I':
                cin >> a >> b;
                addToNum(a, b);
                break;
            case 'D':
                cin >> a;
                removeAtNum(a);
                break;
            case 'C':
                cin >> a >> b;
                changeAtNum(a, b);
                break;
            }
        }

        cout << '#' << test_case << ' ';
        Node* search = head->next;
        for (int i = 0; search != tail && i < L; i++) {
            search = search->next;
        }
        if (search != tail) {
            cout << search->data;
        }
        else {
            cout << -1;
        }
        cout << endl;
    }

    return 0;
}