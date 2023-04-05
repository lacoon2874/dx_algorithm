#include <cstring>

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define DIR_MAX 50000
#define CHILD_MAX 30

struct Directory {
    char name[NAME_MAXLEN + 1];
    int count;
    Directory* child[CHILD_MAX];
};

struct Element {
    Directory* src;
    Directory* dst;
    Element* next;
};

class Stack {
    int count;
    Element* top;
    Element element_pool[DIR_MAX];

public:
    void init() {
        count = 0;
        top = nullptr;
    }

    void push(Directory* s, Directory* d) {
        element_pool[count].src = s;
        element_pool[count].dst = d;
        element_pool[count].next = top;
        top = &element_pool[count++];
    }

    Element pop() {
        top = top->next;
        return element_pool[--count];
    }

    bool empty() {
        if (top) {
            return false;
        }
        else {
            return true;
        }
    }
};

int dirCount;
Directory dir[DIR_MAX];
Directory* root;
Stack stack;

Directory* getDir(char name[NAME_MAXLEN + 1]) {
    strcpy(dir[dirCount].name, name);
    dir[dirCount].count = 0;
    return &dir[dirCount++];
}

Directory* findDir(char path[PATH_MAXLEN + 1]) {
    Directory* search = root;
    int index = 1, length = strlen(path);
    char childDir[NAME_MAXLEN + 1];
    while (index < length) {
        int start = index;
        for (; path[index] != '/'; index++) {}
        strncpy(childDir, path + start, index - start);
        childDir[index - start] = 0;
        for (int i = 0; i < search->count; i++) {
            if (strcmp(childDir, search->child[i]->name) == 0) {
                search = search->child[i];
                break;
            }
        }
        index++;
    }

    return search;
}

void init(int n) {
    dirCount = 0;
    char rootDir[NAME_MAXLEN + 1] = { 0, };
    root = getDir(rootDir);
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    Directory* ptr = findDir(path);
    ptr->child[ptr->count++] = getDir(name);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
    if (path[1] == 0) {
        root = nullptr;
    }
    else {
        char childDir[NAME_MAXLEN + 1];
        char parentPath[PATH_MAXLEN + 1];
        int start, length = strlen(path);
        for (start = length - 2; path[start] != '/'; start--) {}
        strncpy(childDir, path + start + 1, length - start - 2);
        childDir[length - start - 2] = 0;
        strncpy(parentPath, path, start + 1);
        parentPath[start + 1] = 0;

        Directory* ptr = findDir(parentPath);
        for (int i = 0; i < ptr->count; i++) {
            if (strcmp(ptr->child[i]->name, childDir) == 0) {
                ptr->child[i] = ptr->child[--ptr->count];
            }
        }
    }
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    Directory* src = findDir(srcPath);
    Directory* dst = findDir(dstPath);

    dst->child[dst->count++] = getDir(src->name);
    if (src->count) {
        stack.init();
        stack.push(src, dst->child[dst->count - 1]);
        while (!stack.empty()) {
            Element cur = stack.pop();
            for (int i = 0; i < cur.src->count; i++) {
                cur.dst->child[cur.dst->count++] = getDir(cur.src->child[i]->name);
                if (cur.src->child[i]->count) {
                    stack.push(cur.src->child[i], cur.dst->child[i]);
                }
            }
        }
    }
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    char childDir[NAME_MAXLEN + 1];
    char parentPath[PATH_MAXLEN + 1];
    int start, length = strlen(srcPath);
    for (start = length - 2; srcPath[start] != '/'; start--) {}
    strncpy(childDir, srcPath + start + 1, length - start - 2);
    childDir[length - start - 2] = 0;
    strncpy(parentPath, srcPath, start + 1);
    parentPath[start + 1] = 0;

    Directory* src = findDir(parentPath);
    Directory* dst = findDir(dstPath);

    for (int i = 0; i < src->count; i++) {
        if (strcmp(src->child[i]->name, childDir) == 0) {
            Directory* temp = src->child[i];
            src->child[i] = src->child[--src->count];
            dst->child[dst->count++] = temp;
        }
    }
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
    Directory* search = findDir(path);

    int answer = 0;
    if (search->count) {
        stack.init();
        stack.push(search, nullptr);
        while (!stack.empty()) {
            search = stack.pop().src;
            answer += search->count;
            for (int i = 0; i < search->count; i++) {
                if (search->child[i]->count) {
                    stack.push(search->child[i], nullptr);
                }
            }
        }
    }

    return answer;
}