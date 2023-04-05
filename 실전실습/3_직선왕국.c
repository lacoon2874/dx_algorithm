#include <queue>
#include <cstring>

#define CITY_MAX 200

enum { STORE = 1, EXPECT = 2, CITY = 3, CAPITAL = 4 };

struct Element {
    int time;
    int city;
    int amount;
    int option;

    Element(int t, int c, int a, int o) : time(t), city(c), amount(a), option(o) {}

    bool operator<(const Element& e) const {
        if (this->time == e.time) {
            return this->option > e.option;
        }
        else {
            return this->time > e.time;
        }
    }
};

int nSize, mNum;
int store[CITY_MAX], expect[CITY_MAX];
bool valid[CITY_MAX];
std::priority_queue<Element> pq;

int check(int);

int absDiff(int a, int b) {
    if (a > b) {
        return a - b;
    }
    else {
        return b - a;
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

void init(int N, int M)
{
    nSize = N;
    mNum = M;
    std::memset(store, 0, sizeof(int) * CITY_MAX);
    std::memset(expect, 0, sizeof(int) * CITY_MAX);
    std::memset(valid, true, sizeof(bool) * CITY_MAX);
}

void destroy()
{
    while (!pq.empty()) {
        pq.pop();
    }
}

int order(int tStamp, int mCityA, int mCityB, int mTax)
{
    pq.emplace(tStamp + absDiff(mCityA, mCityB), mCityB, mTax, STORE);
    pq.emplace(max(tStamp + absDiff(mCityA, mCityB) - mCityB, tStamp), mCityB, mTax, EXPECT);

    return check(tStamp);
}

int check(int tStamp)
{
    while (!pq.empty() && pq.top().time <= tStamp) {
        int curTime = pq.top().time;
        while (!pq.empty() && pq.top().time == curTime) {
            Element cur = pq.top();
            if (cur.option > EXPECT) {
                break;
            }
            pq.pop();

            if (cur.option == STORE) {
                store[cur.city] += cur.amount;
            }
            else {
                expect[cur.city] += cur.amount;
            }
        }
        while (!pq.empty() && pq.top().time == curTime) {
            Element cur = pq.top();
            pq.pop();

            if (cur.option == CITY) {
                pq.emplace(curTime + cur.city, cur.city, store[cur.city], CAPITAL);
                expect[cur.city] -= store[cur.city];
                store[cur.city] = 0;
            }
            else {
                store[0] += cur.amount;
                mNum++;
                valid[cur.city] = true;
            }
        }
        while (mNum) {
            int max = 0, index = 0;
            for (int i = 1; i < nSize; i++) {
                if (valid[i] && expect[i] > max) {
                    max = expect[i];
                    index = i;
                }
            }
            if (index) {
                pq.emplace(curTime + index, index, 0, CITY);
                mNum--;
                valid[index] = false;
            }
            else {
                break;
            }
        }
    }

    return store[0];
}