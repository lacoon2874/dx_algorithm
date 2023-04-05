#include<iostream>
#include <stack>

#define MAX_SIZE 10000

using namespace std;

struct Node {
    int data;
    Node* parent;
    Node* lchild;
    Node* rchild;
    bool visit;
};

Node node[MAX_SIZE + 1];

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int v, e, a, b;
        cin >> v >> e >> a >> b;

        for (int i = 1; i <= v; i++) {
            node[i].data = i;
            node[i].parent = nullptr;
            node[i].lchild = nullptr;
            node[i].rchild = nullptr;
            node[i].visit = false;
        }

        int parent, child;
        for (int i = 1; i <= e; i++) {
            cin >> parent >> child;
            if (!node[parent].lchild) {
                node[parent].lchild = &node[child];
            }
            else {
                node[parent].rchild = &node[child];
            }
            node[child].parent = &node[parent];
        }

        for (Node* ptr = &node[a]; ptr; ptr = ptr->parent) {
            ptr->visit = true;
        }

        Node* search = &node[b];
        for (; search; search = search->parent) {
            if (search->visit) {
                break;
            }
        }
        cout << '#' << test_case << ' ' << search->data << ' ';

        int answer = 1;
        stack<Node*> stk;
        stk.push(search);
        while (!stk.empty()) {
            search = stk.top();
            stk.pop();

            if (search->rchild) {
                answer++;
                stk.push(search->rchild);
            }
            if (search->lchild) {
                answer++;
                stk.push(search->lchild);
            }
        }

        cout << answer << endl;
    }

    return 0;
}