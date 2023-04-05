#include<iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int d) : data(d) {
        next = nullptr;
        prev = nullptr;
    }
};

int main(int argc, char** argv)
{
    int test_case;
    int T = 10;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        Node* head = new Node(-1), * tail = new Node(-1);
        head->next = tail;
        tail->prev = head;

        int n, p;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> p;
            Node* temp = new Node(p);
            temp->prev = tail->prev;
            temp->next = tail;
            temp->prev->next = temp;
            tail->prev = temp;
        }

        int m, x, y, s;
        char o;
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> o;
            Node* search;
            switch (o) {
            case 'I':
                cin >> x >> y;
                search = head;
                for (int j = 1; j <= x; j++) {
                    search = search->next;
                }
                for (int j = 0; j < y; j++) {
                    cin >> s;
                    Node* temp = new Node(s);
                    temp->next = search->next;
                    temp->prev = search;
                    temp->next->prev = temp;
                    search->next = temp;
                    search = search->next;
                }
                break;
            case 'D':
                cin >> x >> y;
                search = head;
                for (int j = 1; j <= x; j++) {
                    search = search->next;
                }
                for (int j = 0; j < y; j++) {
                    Node* temp = search->next;
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    delete temp;
                }
                break;
            case 'A':
                cin >> y;
                for (int j = 0; j < y; j++) {
                    cin >> s;
                    Node* temp = new Node(s);
                    temp->prev = tail->prev;
                    temp->next = tail;
                    temp->prev->next = temp;
                    tail->prev = temp;
                }
                break;
            }
        }

        cout << '#' << test_case << ' ';
        Node* search = head->next;
        for (int i = 0; i < 10; i++) {
            cout << search->data << ' ';
            search = search->next;
        }
        cout << endl;
    }

    return 0;
}