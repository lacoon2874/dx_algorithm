#include <queue>

#define MAX_NODE 60
#define MAX_SIZE 30000
#define INF 1000000

struct List {
    int endAirport;
    int startTime;
    int travelTime;
    int price;
    List* next;
};

struct Element {
    int airport;
    int cost;

    Element(int a, int c) : airport(a), cost(c) {}

    bool operator<(const Element& e) const {
        return this->cost > e.cost;
    }
};

List* head[MAX_NODE];
List list_pool[MAX_SIZE];
int nSize, listCount;
int minCost[MAX_NODE][MAX_NODE];

void init(int N)
{
    nSize = N;
    listCount = 0;
    for (int i = 0; i < nSize; i++) {
        head[i] = nullptr;
        for (int j = 0; j < nSize; j++) {
            minCost[i][j] = INF;
        }
        minCost[i][i] = 0;
    }
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
    list_pool[listCount].endAirport = mEndAirport;
    list_pool[listCount].startTime = mStartTime;
    list_pool[listCount].travelTime = mTravelTime;
    list_pool[listCount].price = mPrice;
    list_pool[listCount].next = head[mStartAirport];
    head[mStartAirport] = &list_pool[listCount++];

    bool visit[MAX_NODE];
    for (int start = 0; start < nSize; start++) {
        if (mPrice + minCost[start][mStartAirport] < minCost[start][mEndAirport]) {
            minCost[start][mEndAirport] = mPrice + minCost[start][mStartAirport];
            for (int i = 0; i < nSize; i++) {
                visit[i] = false;
            }
            std::priority_queue<Element> pq;
            pq.emplace(mEndAirport, minCost[start][mEndAirport]);
            while (!pq.empty()) {
                Element cur = pq.top();
                pq.pop();
                if (!visit[cur.airport]) {
                    visit[cur.airport] = true;
                    for (List* ptr = head[cur.airport]; ptr; ptr = ptr->next) {
                        if (!visit[ptr->endAirport] && cur.cost + ptr->price < minCost[start][ptr->endAirport]) {
                            minCost[start][ptr->endAirport] = cur.cost + ptr->price;
                            pq.emplace(ptr->endAirport, minCost[start][ptr->endAirport]);
                        }
                    }
                }
            }
        }
    }
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
    int minTime[MAX_NODE];
    bool visit[MAX_NODE];
    for (int i = 0; i < nSize; i++) {
        minTime[i] = INF;
        visit[i] = false;
    }
    minTime[mStartAirport] = mStartTime;

    std::priority_queue<Element> pq;
    pq.emplace(mStartAirport, mStartTime);
    while (!pq.empty()) {
        Element cur = pq.top();
        pq.pop();
        if (!visit[cur.airport]) {
            visit[cur.airport] = true;
            for (List* ptr = head[cur.airport]; ptr; ptr = ptr->next) {
                if (!visit[ptr->endAirport]) {
                    int time = cur.cost + ptr->travelTime + ptr->startTime - (cur.cost % 24);
                    if (cur.cost % 24 > ptr->startTime) {
                        time += 24;
                    }
                    if (time < minTime[ptr->endAirport]) {
                        minTime[ptr->endAirport] = time;
                        pq.emplace(ptr->endAirport, time);
                    }
                }
            }
        }
    }

    if (minTime[mEndAirport] == INF) {
        return -1;
    }
    return (minTime[mEndAirport] - mStartTime);
}

int minPrice(int mStartAirport, int mEndAirport)
{
    if (minCost[mStartAirport][mEndAirport] == INF) {
        return -1;
    }
    return minCost[mStartAirport][mEndAirport];
}