#define MAX_N 1000

struct List {
    int data;
    List* next;
};

struct Element {
    int size;
    int pos;
};

struct Stack {
    int index;
    int from;
    int to;
    Stack* next;
};

int count, stackCount;
Element disk[MAX_N], mergeTemp[MAX_N];
List* pillar[3];
List list_pool[MAX_N];
Stack* top;
Stack stack_pool[MAX_N];

void merge(int, int, int);

void mergeSort(int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void merge(int l, int m, int r) {
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (disk[i].size > disk[j].size) {
            mergeTemp[k++] = disk[i++];
        }
        else {
            mergeTemp[k++] = disk[j++];
        }
    }
    while (i <= m) {
        mergeTemp[k++] = disk[i++];
    }
    while (j <= r) {
        mergeTemp[k++] = disk[j++];
    }
    for (k = l; k <= r; k++) {
        disk[k] = mergeTemp[k];
    }
}

int getValid(int a, int b) {
    if (a == 0) {
        if (b == 1) {
            return 2;
        }
        else {
            return 1;
        }
    }
    else if (a == 1) {
        if (b == 0) {
            return 2;
        }
        else {
            return 0;
        }
    }
    else {
        if (b == 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

void push(int index, int from, int to) {
    stack_pool[stackCount].index = index;
    stack_pool[stackCount].from = from;
    stack_pool[stackCount].to = to;
    stack_pool[stackCount].next = top;
    top = &stack_pool[stackCount++];
}

Stack* pop() {
    Stack* ret_val = top;
    top = top->next;
    stackCount--;
    return ret_val;
}

void init(int N[3], int mDisk[3][MAX_N])
{
    count = 0;
    top = nullptr;
    stackCount = 0;
    for (int i = 0; i < 3; i++) {
        pillar[i] = nullptr;
        for (int j = N[i] - 1; j >= 0; j--) {
            disk[count].size = mDisk[i][j];
            disk[count].pos = i;
            list_pool[count].data = mDisk[i][j];
            list_pool[count].next = pillar[i];
            pillar[i] = &list_pool[count++];
        }
    }
    mergeSort(0, count - 1);
    int valid = 2;
    for (int i = 0; i < count; i++) {
        push(i, disk[i].pos, valid);
        if (disk[i].pos != valid) {
            if (pillar[disk[i].pos]->data == disk[i].size && (!pillar[valid] || pillar[valid]->data > disk[i].size)) {
                break;
            }
            valid = getValid(disk[i].pos, valid);
        }
    }
}

void destroy()
{

}

void go(int k, int mTop[3])
{
    for (int i = 0; top && i < k; i++) {
        Stack* cur = pop();

        List* temp = pillar[cur->from];
        pillar[cur->from] = temp->next;
        temp->next = pillar[cur->to];
        pillar[cur->to] = temp;
        disk[cur->index].pos = cur->to;

        if (cur->index == count - 1) {
            while (top && top->from == top->to) {
                cur = pop();
            }
        }
        else {
            int valid = cur->to;
            for (int j = cur->index; j < count; j++) {
                push(j, disk[j].pos, valid);
                if (disk[j].pos != valid) {
                    if (pillar[disk[j].pos]->data == disk[j].size && (!pillar[valid] || pillar[valid]->data > disk[j].size)) {
                        break;
                    }
                    valid = getValid(disk[j].pos, valid);
                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (pillar[i]) {
            mTop[i] = pillar[i]->data;
        }
        else {
            mTop[i] = 0;
        }
    }
}