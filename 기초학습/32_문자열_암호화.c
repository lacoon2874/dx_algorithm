#include <cstring>

class Hash {
    struct List {
        int data;
        List* next;
    };

    List list_pool[50000];
    List* head[17576];
    int listCount;
    char str[50005];
    int len;

    void insert(int data, int h) {
        List* search = head[h], * before = nullptr;
        for (; search; before = search, search = search->next) {
            if (data < search->data) {
                break;
            }
        }

        list_pool[listCount].data = data;
        list_pool[listCount].next = search;
        if (!before) {
            head[h] = &list_pool[listCount++];
        }
        else {
            before->next = &list_pool[listCount++];
        }
    }

    void move(int data, int from, int to) {
        List* search = head[from], * before = nullptr;
        for (; search; before = search, search = search->next) {
            if (search->data == data) {
                break;
            }
        }
        List* ptr = search;
        if (!before) {
            head[from] = search->next;
        }
        else {
            before->next = search->next;
        }

        search = head[to], before = nullptr;
        for (; search; before = search, search = search->next) {
            if (search->data > data) {
                break;
            }
        }
        ptr->next = search;
        if (!before) {
            head[to] = ptr;
        }
        else {
            before->next = ptr;
        }
    }

public:
    void init(int n, char init_string[]) {
        for (int i = 0; i < 17576; i++) {
            head[i] = nullptr;
        }
        listCount = 0;
        std::memset(str, 0, sizeof(char) * 50005);
        len = n;
        strcpy(str, init_string);

        int offset = 26 * 26 * 26, cur = 0;
        for (int i = 0; i < 2; i++) {
            cur = (cur * 26) + (init_string[i] - 'a');
        }
        for (int i = 2; i < len; i++) {
            cur = ((cur * 26) % offset) + (init_string[i] - 'a');
            insert(i - 2, cur);
        }
    }

    int change(char string_A[], char string_B[]) {
        int a = 0, offset = 26 * 26 * 26;
        for (int i = 0; i < 3; i++) {
            a = (a * 26) + (string_A[i] - 'a');
        }
        int before = -1, count = 0;
        while (true) {
            int cur = -1;
            for (List* search = head[a]; search; search = search->next) {
                if (search->data > before) {
                    cur = search->data;
                    break;
                }
            }
            if (cur == -1) {
                break;
            }

            int from = 0, to;
            for (int i = cur - 2; i < cur; i++) {
                if (i >= 0) {
                    from = (from * 26) + (str[i] - 'a');
                }
            }
            to = from;
            for (int i = cur - 2, j = 0; i <= cur; i++, j++) {
                from = ((from * 26) % offset) + (str[i + 2] - 'a');
                str[i + 2] = string_B[j];
                to = ((to * 26) % offset) + (str[i + 2] - 'a');
                if (i >= 0 && i < len - 2) {
                    move(i, from, to);
                }
            }
            for (int i = cur + 1; i <= cur + 2; i++) {
                from = ((from * 26) % offset) + (str[i + 2] - 'a');
                to = ((to * 26) % offset) + (str[i + 2] - 'a');
                if (i >= 0 && i < len - 2) {
                    move(i, from, to);
                }
            }

            before = cur + 2;
            count++;
        }

        return count;
    }

    void getString(char ret[]) {
        strcpy(ret, str);
    }
};

Hash hash;

void init(int n, char init_string[]) {
    hash.init(n, init_string);
}

int change(char string_A[], char string_B[]) {
    return hash.change(string_A, string_B);
}

void result(char ret[]) {
    hash.getString(ret);
}