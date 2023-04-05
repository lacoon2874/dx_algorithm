#define MAX_N 100001

struct Element {
    int parent;
    int score;
};

struct Stack {
    int index;
    int score;
    Stack* next;
};

Element group[MAX_N];
Stack stack_pool[MAX_N];

int find(int node) {
    int p, count = 0;
    Stack* top = nullptr;

    for (p = node; p != group[p].parent; p = group[p].parent) {
        stack_pool[count].index = p;
        stack_pool[count].score = group[p].score;
        stack_pool[count].next = top;
        top = &stack_pool[count++];
    }

    if (top) {
        top = top->next;
    }
    while (top) {
        group[top->index].score += group[group[top->index].parent].score;
        group[top->index].parent = p;
        top = top->next;
    }

    return p;
}

void init(int N)
{
    for (int i = 1; i <= N; i++) {
        group[i].parent = i;
        group[i].score = 0;
    }
}

void updateScore(int mWinnerID, int mLoserID, int mScore)
{
    int wp = find(mWinnerID);
    int lp = find(mLoserID);

    group[wp].score += mScore;
    group[lp].score -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB)
{
    int ap = find(mPlayerA);
    int bp = find(mPlayerB);

    group[bp].score -= group[ap].score;
    group[bp].parent = ap;
}

int getScore(int mID)
{
    int p = find(mID);

    if (p == mID) {
        return group[p].score;
    }
    else {
        return group[p].score + group[mID].score;
    }
}