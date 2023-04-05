#define USER_MAX 1000
#define FOLLOW_MAX 100000
#define POST_MAX 100000

struct List {
    int id;
    List* next;
};

struct Post {
    int like;
    int timestamp;
};

struct Element {
    int like;
    int timeDif;
    int pid;

    bool operator<(const Element& e) const {
        if (this->timeDif > 1000 && e.timeDif > 1000) {
            return this->timeDif > e.timeDif;
        }
        else if (this->timeDif > 1000) {
            return true;
        }
        else if (e.timeDif > 1000) {
            return false;
        }
        else {
            if (this->like == e.like) {
                return this->timeDif > e.timeDif;
            }
            return this->like < e.like;
        }
    }

    bool operator>(const Element& e) const {
        return e < *this;
    }
};

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

class Heap {
    Element array[POST_MAX + 1];
    int count;

public:
    void init() {
        count = 0;
    }

    void push(int like, int timeDif, int pid) {
        int cur = ++count;
        array[cur].like = like;
        array[cur].timeDif = timeDif;
        array[cur].pid = pid;

        while (cur != 1) {
            if (array[cur] < array[cur / 2]) {
                break;
            }
            swap(array[cur], array[cur / 2]);
            cur /= 2;
        }
    }

    Element pop() {
        Element retVal = array[1];
        array[1] = array[count--];

        int parent = 1;
        while (2 * parent <= count) {
            int child = 2 * parent;
            if (child + 1 <= count && array[child + 1] > array[child]) {
                child++;
            }
            if (array[parent] > array[child]) {
                break;
            }
            swap(array[parent], array[child]);
            parent = child;
        }

        return retVal;
    }

    bool empty() {
        return (count <= 0 ? true : false);
    }
};

List* userFollow[USER_MAX + 1], * userPost[USER_MAX + 1];
List follow_pool[FOLLOW_MAX], post_pool[POST_MAX];
Post post[POST_MAX + 1];
int followCount, postCount, nSize;
Heap heap;

void init(int N)
{
    nSize = N;
    for (int i = 1; i <= nSize; i++) {
        userFollow[i] = nullptr;
        userPost[i] = nullptr;
    }
    followCount = 0;
    postCount = 0;
}

void follow(int uID1, int uID2, int timestamp)
{
    follow_pool[followCount].id = uID2;
    follow_pool[followCount].next = userFollow[uID1];
    userFollow[uID1] = &follow_pool[followCount++];
}

void makePost(int uID, int pID, int timestamp)
{
    post_pool[postCount].id = pID;
    post_pool[postCount].next = userPost[uID];
    userPost[uID] = &post_pool[postCount++];
    post[pID].like = 0;
    post[pID].timestamp = timestamp;
}

void like(int pID, int timestamp)
{
    post[pID].like++;
}

void getFeed(int uID, int timestamp, int pIDList[])
{
    heap.init();
    for (List* search = userPost[uID]; search; search = search->next) {
        heap.push(post[search->id].like, timestamp - post[search->id].timestamp, search->id);
    }
    for (List* ptr = userFollow[uID]; ptr; ptr = ptr->next) {
        for (List* search = userPost[ptr->id]; search; search = search->next) {
            heap.push(post[search->id].like, timestamp - post[search->id].timestamp, search->id);
        }
    }
    for (int i = 0; !heap.empty() && i < 10; i++) {
        Element cur = heap.pop();
        pIDList[i] = cur.pid;
    }
}