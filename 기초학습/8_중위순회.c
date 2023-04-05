#include<iostream>
#include <stack>

#define MAX_SIZE 100

using namespace std;

struct Node {
    char data;
    Node* lchild;
    Node* rchild;
};

Node node[MAX_SIZE + 1];

int main(int argc, char** argv)
{
    int test_case;

    for (test_case = 1; test_case <= 10; ++test_case)
    {
        int n;
        cin >> n;

        for (int i = 1; i <= n; i++) {
            int a, b, c;
            if (i * 2 + 1 <= n) {
                cin >> a >> node[i].data >> b >> c;
                node[i].lchild = &node[b];
                node[i].rchild = &node[c];
            }
            else if (i * 2 <= n) {
                cin >> a >> node[i].data >> b;
                node[i].lchild = &node[b];
                node[i].rchild = nullptr;
            }
            else {
                cin >> a >> node[i].data;
                node[i].lchild = nullptr;
                node[i].rchild = nullptr;
            }
        }

        Node* search = &node[1];
        stack<Node*> stk;
        cout << '#' << test_case << ' ';
        while (true) {
            while (search != nullptr) {
                stk.push(search);
                search = search->lchild;
            }
            if (stk.empty()) {
                break;
            }
            search = stk.top();
            stk.pop();
            cout << search->data;
            search = search->rchild;
        }
        cout << '\n';
    }

    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}