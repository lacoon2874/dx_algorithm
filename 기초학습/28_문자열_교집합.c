#include<iostream>
#include <string>

#define BUCKET 200003

using namespace std;

struct List {
    string data;
    List* next;
};

List list_pool[100010];
List* head[BUCKET];

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n, m;
        int index = 0;
        string input;

        cin >> n >> m;
        for (int i = 0; i < BUCKET; i++) {
            head[i] = nullptr;
        }

        for (int i = 0; i < n; i++) {
            cin >> input;
            unsigned long long hash = 5381;
            for (int j = 0; j < static_cast<int>(input.length()) && j < 10; j++) {
                hash = (hash << 5) + hash + (input[j] - 'a');
            }
            hash %= BUCKET;
            list_pool[index].data = input;
            list_pool[index].next = head[hash];
            head[hash] = &list_pool[index++];
        }

        int answer = 0;
        for (int i = 0; i < m; i++) {
            cin >> input;
            unsigned long long hash = 5381;
            for (int j = 0; j < static_cast<int>(input.length()) && j < 10; j++) {
                hash = (hash << 5) + hash + (input[j] - 'a');
            }
            hash %= BUCKET;
            for (List* ptr = head[hash]; ptr; ptr = ptr->next) {
                if (ptr->data.compare(input) == 0) {
                    answer++;
                    break;
                }
            }
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}