#include <iostream>
#include <queue>

using namespace std;

struct Element {
    int index1;
    int index2;
    long long len;

    Element(int i1, int i2, long long l) : index1(i1), index2(i2), len(l) {}

    bool operator<(const Element& e) const {
        return this->len > e.len;
    }
};

int main(int argc, char** argv)
{
    int test_case;
    int T;
    long long x[1000], y[1000];
    int parent[1000];

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int n;
        cin >> n;
        double e;

        priority_queue<Element> pq;
        for (int i = 0; i < n; i++) {
            cin >> x[i];
            parent[i] = i;
        }
        cin >> y[0];
        for (int i = 1; i < n; i++) {
            cin >> y[i];
            for (int j = 0; j < i; j++) {
                pq.emplace(j, i, (y[i] - y[j]) * (y[i] - y[j]) + (x[i] - x[j]) * (x[i] - x[j]));
            }
        }
        cin >> e;

        int count = 1;
        long long answer = 0;
        while (count < n) {
            Element cur = pq.top();
            pq.pop();

            int a = cur.index1;
            int b = cur.index2;
            for (; a != parent[a]; a = parent[a]) {}
            for (; b != parent[b]; b = parent[b]) {}

            if (a != b) {
                parent[b] = a;
                count++;
                answer += cur.len;
            }
        }

        cout << fixed;
        cout.precision(0);
        cout << '#' << test_case << ' ' << e * answer << endl;
    }

    return 0;
}