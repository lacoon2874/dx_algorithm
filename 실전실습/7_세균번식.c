#include <queue>
#include <stack>
#include <utility>

#define MAX_N 100

struct Element {
    int energy;
    int type;
    bool valid;
};

struct Pos {
    int row;
    int col;
    int energy;

    Pos(int r, int c, int e) : row(r), col(c), energy(e) {}

    bool operator<(const Pos& p) const {
        if (this->energy == p.energy) {
            if (this->row == p.row) {
                return this->col > p.col;
            }
            else {
                return this->row > p.row;
            }
        }
        else {
            return this->energy < p.energy;
        }
    }
};

Element dish[MAX_N][MAX_N];
int nSize;

void init(int N, int mDish[MAX_N][MAX_N])
{
    nSize = N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dish[i][j].energy = mDish[i][j];
            dish[i][j].type = 0;
            dish[i][j].valid = false;
        }
    }
}

int dropMedicine(int mTarget, int mRow, int mCol, int mEnergy)
{
    int row = mRow - 1, col = mCol - 1;

    if (dish[row][col].type == 0) {
        mEnergy -= dish[row][col].energy;
        mEnergy = mEnergy > 0 ? mEnergy : 0;
        dish[row][col].type = mTarget;
    }
    else {
        if (dish[row][col].type != mTarget) {
            mEnergy = 0;
        }
    }

    std::stack<std::pair<int, int>> stk;
    std::priority_queue<Pos> pq;
    dish[row][col].valid = true;
    while (mEnergy) {
        stk.emplace(row, col);
        while (!stk.empty()) {
            std::pair<int, int> cur = stk.top();
            stk.pop();
            row = cur.first;
            col = cur.second;

            if (row - 1 >= 0 && !dish[row - 1][col].valid) {
                if (dish[row - 1][col].type == 0) {
                    pq.emplace(row - 1, col, dish[row - 1][col].energy);
                }
                else if (dish[row - 1][col].type == mTarget) {
                    stk.emplace(row - 1, col);
                }
                dish[row - 1][col].valid = true;
            }
            if (col - 1 >= 0 && !dish[row][col - 1].valid) {
                if (dish[row][col - 1].type == 0) {
                    pq.emplace(row, col - 1, dish[row][col - 1].energy);
                }
                else if (dish[row][col - 1].type == mTarget) {
                    stk.emplace(row, col - 1);
                }
                dish[row][col - 1].valid = true;
            }
            if (row + 1 < nSize && !dish[row + 1][col].valid) {
                if (dish[row + 1][col].type == 0) {
                    pq.emplace(row + 1, col, dish[row + 1][col].energy);
                }
                else if (dish[row + 1][col].type == mTarget) {
                    stk.emplace(row + 1, col);
                }
                dish[row + 1][col].valid = true;
            }
            if (col + 1 < nSize && !dish[row][col + 1].valid) {
                if (dish[row][col + 1].type == 0) {
                    pq.emplace(row, col + 1, dish[row][col + 1].energy);
                }
                else if (dish[row][col + 1].type == mTarget) {
                    stk.emplace(row, col + 1);
                }
                dish[row][col + 1].valid = true;
            }
        }

        if (pq.empty()) {
            break;
        }
        Pos topPos = pq.top();
        pq.pop();
        row = topPos.row;
        col = topPos.col;

        mEnergy -= dish[row][col].energy;
        mEnergy = mEnergy > 0 ? mEnergy : 0;
        dish[row][col].type = mTarget;
    }

    int count = 0;
    for (int i = 0; i < nSize; i++) {
        for (int j = 0; j < nSize; j++) {
            if (dish[i][j].type == mTarget) {
                count++;
            }
            dish[i][j].valid = false;
        }
    }

    return count;
}

int cleanBacteria(int mRow, int mCol)
{
    int row = mRow - 1, col = mCol - 1, type = dish[row][col].type;
    if (dish[row][col].type == 0) {
        return -1;
    }

    std::stack<std::pair<int, int>> stk;
    stk.emplace(row, col);
    dish[row][col].valid = true;
    while (!stk.empty()) {
        std::pair<int, int> cur = stk.top();
        stk.pop();
        row = cur.first;
        col = cur.second;
        dish[row][col].type = 0;

        if (row - 1 >= 0 && !dish[row - 1][col].valid) {
            if (dish[row - 1][col].type == type) {
                stk.emplace(row - 1, col);
            }
            dish[row - 1][col].valid = true;
        }
        if (col - 1 >= 0 && !dish[row][col - 1].valid) {
            if (dish[row][col - 1].type == type) {
                stk.emplace(row, col - 1);
            }
            dish[row][col - 1].valid = true;
        }
        if (row + 1 < nSize && !dish[row + 1][col].valid) {
            if (dish[row + 1][col].type == type) {
                stk.emplace(row + 1, col);
            }
            dish[row + 1][col].valid = true;
        }
        if (col + 1 < nSize && !dish[row][col + 1].valid) {
            if (dish[row][col + 1].type == type) {
                stk.emplace(row, col + 1);
            }
            dish[row][col + 1].valid = true;
        }
    }

    int count = 0;
    for (int i = 0; i < nSize; i++) {
        for (int j = 0; j < nSize; j++) {
            if (dish[i][j].type == type) {
                count++;
            }
            dish[i][j].valid = false;
        }
    }

    return count;
}