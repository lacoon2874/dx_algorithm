struct Element {
    int id;
    int income;

    bool operator<(const Element& e) const {
        if (this->income == e.income) {
            return this->id > e.id;
        }
        return this->income < e.income;
    }

    bool operator>(const Element& e) const {
        if (this->income == e.income) {
            return this->id < e.id;
        }
        return this->income > e.income;
    }
};

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

class Heap {
    Element array[100001];
    int count;

public:
    void init() {
        count = 0;
    }

    void push(int id, int income) {
        int cur = ++count;
        array[cur].id = id;
        array[cur].income = income;

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
        swap(array[1], array[count--]);

        int cur = 1;
        while (2 * cur <= count) {
            int child = 2 * cur;
            if (child + 1 <= count && array[child + 1] > array[child]) {
                child += 1;
            }
            if (array[cur] > array[child]) {
                break;
            }
            swap(array[cur], array[child]);
            cur = child;
        }

        return retVal;
    }

    bool empty() {
        return (count <= 0 ? true : false);
    }
};

Heap heap;

void init()
{
    heap.init();
}

void addUser(int uID, int height)
{
    heap.push(uID, height);
}

int getTop10(int result[10])
{
    int count = 0;
    Element temp[10];
    for (; !heap.empty() && count < 10; count++) {
        temp[count] = heap.pop();
        result[count] = temp[count].id;
    }
    for (int i = 0; i < count; i++) {
        heap.push(temp[i].id, temp[i].income);
    }

    return count;
}