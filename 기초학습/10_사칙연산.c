#include <iostream>
#include <string>
#include <stack>

#define MAX_SIZE 1000

using namespace std;

struct Node {
    union U {
        char ch;
        int num;
    }data;
    Node* lchild;
    Node* rchild;
    bool visit;
};

Node node[MAX_SIZE + 1];

int main(int argc, char** argv)
{
    int test_case;

    for (test_case = 1; test_case <= 10; ++test_case)
    {
        int n;
        cin >> n;

        int a, b, c;
        string str;
        for (int i = 1; i <= n; i++) {
            cin >> a >> str;
            if (str[0] < '0' || str[0] > '9') {
                cin >> b >> c;
                node[i].data.ch = str[0];
                node[i].lchild = &node[b];
                node[i].rchild = &node[c];
            }
            else {
                node[i].data.num = stoi(str);
                node[i].lchild = nullptr;
                node[i].rchild = nullptr;
            }
            node[i].visit = false;
        }

        stack<Node*> stk;
        stack<int> answer;
        Node* search = &node[1];
        stk.push(search);
        while (!stk.empty()) {
            search = stk.top();
            stk.pop();

            if (!search->visit && search->lchild) {
                search->visit = true;
                stk.push(search);
                stk.push(search->rchild);
                stk.push(search->lchild);
            }
            else {
                if (search->lchild) {
                    b = answer.top();
                    answer.pop();
                    a = answer.top();
                    answer.pop();

                    switch (search->data.ch) {
                    case '+':
                        answer.push(a + b);
                        break;
                    case '-':
                        answer.push(a - b);
                        break;
                    case '*':
                        answer.push(a * b);
                        break;
                    case '/':
                        answer.push(a / b);
                        break;
                    }
                }
                else {
                    answer.push(search->data.num);
                }
            }
        }

        cout << '#' << test_case << ' ' << answer.top() << endl;
    }

    return 0;
}