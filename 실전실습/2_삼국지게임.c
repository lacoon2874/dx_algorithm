#include <cstring>
#include <vector>

struct Pos {
    int row;
    int col;

    Pos() {}
    Pos(int r, int c) : row(r), col(c) {}

    bool operator==(const Pos& p) {
        if (this->row == p.row && this->col == p.col) {
            return true;
        }
        return false;
    }

    bool operator!=(const Pos& p) {
        if (this->row == p.row && this->col == p.col) {
            return false;
        }
        return true;
    }
};

class Trie {
    static constexpr size_t M = 26;
    static constexpr char OFFSET = 'a';

    struct TrieNode {
        int child[M];
        bool is_terminal;
        Pos pos;

        TrieNode() {
            std::memset(child, -1, sizeof(int) * M);
            is_terminal = false;
        }
    };

    std::vector< TrieNode > nodes;

public:
    Trie() : nodes(1) {}

    void init() {
        nodes.resize(1);
        nodes[0] = TrieNode();
    }

    void insert(const char str[11], const int r, const int c) {
        int node_id = 0;
        for (int i = 0; str[i] != 0; i++) {
            if (nodes[node_id].child[str[i] - OFFSET] == -1) {
                nodes[node_id].child[str[i] - OFFSET] = nodes.size();
                nodes.emplace_back();
            }
            node_id = nodes[node_id].child[str[i] - OFFSET];
        }
        nodes[node_id].is_terminal = true;
        nodes[node_id].pos.row = r;
        nodes[node_id].pos.col = c;
    }

    void remove(const char str[11]) {
        int node_id = 0;
        for (int i = 0; str[i] != 0; i++) {
            if (nodes[node_id].child[str[i] - OFFSET] == -1) {
                return;
            }
            node_id = nodes[node_id].child[str[i] - OFFSET];
        }
        nodes[node_id].is_terminal = false;
    }

    Pos find(const char str[11]) const {
        int node_id = 0;
        for (int i = 0; str[i] != 0; i++) {
            if (nodes[node_id].child[str[i] - OFFSET] == -1) {
                return Pos();
            }
            node_id = nodes[node_id].child[str[i] - OFFSET];
        }
        return nodes[node_id].pos;
    }
};

struct List {
    Pos data;
    List* next;

    List(int r, int c) : data(r, c), next(nullptr) {}
    ~List() {
        if (next) {
            delete next;
        }
    }
};

int nSize;
Trie trie;
int soldier[25][25];
Pos parent[25][25];
List* alliance[25][25];
unsigned long long hostile[25][25][10];
char monarch[25][25][11];

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
    nSize = N;
    trie.init();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            soldier[i][j] = mSoldier[i][j];
            parent[i][j] = { i, j };
            alliance[i][j] = new List(i, j);
            std::memset(hostile[i][j], 0, sizeof(unsigned long long) * 10);
            std::memset(monarch[i][j], 0, sizeof(char) * 11);
            for (int k = 0; mMonarch[i][j][k] != 0; k++) {
                monarch[i][j][k] = mMonarch[i][j][k];
            }
            trie.insert(monarch[i][j], i, j);
        }
    }
}

void destroy()
{
    for (int i = 0; i < nSize; i++) {
        for (int j = 0; j < nSize; j++) {
            if (alliance[i][j]) {
                delete alliance[i][j];
            }
        }
    }
}

int ally(char mMonarchA[11], char mMonarchB[11])
{
    Pos a = trie.find(mMonarchA);
    Pos b = trie.find(mMonarchB);

    Pos aP, bP;
    for (aP = parent[a.row][a.col]; aP != parent[aP.row][aP.col]; aP = parent[aP.row][aP.col]) {}
    for (bP = parent[b.row][b.col]; bP != parent[bP.row][bP.col]; bP = parent[bP.row][bP.col]) {}

    if (aP == bP) {
        return -1;
    }

    int index = bP.row * nSize + bP.col;
    unsigned long long temp = 1ull << (index % 64);
    if (hostile[aP.row][aP.col][index / 64] & (1ull << (index % 64))) {
        return -2;
    }

    int count = 0;
    index = aP.row * nSize + aP.col;
    int indexB = bP.row * nSize + bP.col;
    for (int i = 0; i <= nSize * nSize / 64; i++) {
        if (hostile[bP.row][bP.col][i]) {
            for (unsigned long long j = 1ull; j; j = j << 1) {
                if (hostile[bP.row][bP.col][i] & j) {
                    Pos cP = parent[count / nSize][count % nSize];
                    for (; cP != parent[cP.row][cP.col]; cP = parent[cP.row][cP.col]) {}
                    hostile[cP.row][cP.col][indexB / 64] &= ~(1ull << (indexB % 64));
                    hostile[cP.row][cP.col][index / 64] |= (1ull << (index % 64));
                }
                count++;
            }
        }
        else {
            count += 64;
        }
    }

    for (int i = 0; i < 10; i++) {
        hostile[aP.row][aP.col][i] |= hostile[bP.row][bP.col][i];
    }
    parent[bP.row][bP.col] = aP;
    List* last = alliance[aP.row][aP.col];
    for (; last->next; last = last->next) {}
    last->next = alliance[bP.row][bP.col];
    alliance[bP.row][bP.col] = nullptr;

    return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
    Pos a = trie.find(mMonarchA);
    Pos b = trie.find(mMonarchB);

    Pos aP, bP;
    for (aP = parent[a.row][a.col]; aP != parent[aP.row][aP.col]; aP = parent[aP.row][aP.col]) {}
    for (bP = parent[b.row][b.col]; bP != parent[bP.row][bP.col]; bP = parent[bP.row][bP.col]) {}

    if (aP == bP) {
        return -1;
    }
    bool isAdj = false;
    int attackCount = 0, defenseCount = 0;
    std::vector<Pos> defense;
    for (int i = b.row - 1; i <= b.row + 1; i++) {
        for (int j = b.col - 1; j <= b.col + 1; j++) {
            if (i == b.row && j == b.col) {
                defenseCount += soldier[i][j];
            }
            else if (i >= 0 && i < nSize && j >= 0 && j < nSize) {
                Pos cP = parent[i][j];
                for (; cP != parent[cP.row][cP.col]; cP = parent[cP.row][cP.col]) {}
                if (cP == aP) {
                    isAdj = true;
                    attackCount += soldier[i][j] / 2;
                    soldier[i][j] -= soldier[i][j] / 2;
                }
                else if (cP == bP) {
                    defenseCount += soldier[i][j] / 2;
                    defense.push_back(Pos(i, j));
                }
            }
        }
    }
    if (!isAdj) {
        return -2;
    }

    for (size_t i = 0; i < defense.size(); i++) {
        soldier[defense[i].row][defense[i].col] -= soldier[defense[i].row][defense[i].col] / 2;
    }

    int indexA = aP.row * nSize + aP.col;
    int indexB = bP.row * nSize + bP.col;
    hostile[aP.row][aP.col][indexB / 64] |= (1ull << (indexB % 64));
    hostile[bP.row][bP.col][indexA / 64] |= (1ull << (indexA % 64));

    if (attackCount > defenseCount) {
        soldier[b.row][b.col] = attackCount - defenseCount;
        trie.remove(mMonarchB);
        trie.insert(mGeneral, b.row, b.col);

        if (b != bP) {
            List* before;
            for (List* bList = alliance[bP.row][bP.col]; bList; bList = bList->next) {
                if (bList->next && bList->next->data == b) {
                    before = bList;
                }
                Pos cur = bList->data;
                parent[cur.row][cur.col] = bP;
            }
            List* temp = before->next;
            before->next = before->next->next;

            parent[b.row][b.col] = aP;
            temp->next = alliance[aP.row][aP.col]->next;
            alliance[aP.row][aP.col]->next = temp;
        }
        else {
            if (alliance[b.row][b.col]->next) {
                bP = alliance[b.row][b.col]->next->data;
                for (int i = 0; i < 10; i++) {
                    hostile[bP.row][bP.col][i] = hostile[b.row][b.col][i];
                }
                for (List* bList = alliance[b.row][b.col]->next; bList; bList = bList->next) {
                    Pos cur = bList->data;
                    parent[cur.row][cur.col] = bP;
                }
                alliance[bP.row][bP.col] = alliance[b.row][b.col]->next;
                int indexBP = bP.row * nSize + bP.col;
                int count = 0;
                for (int i = 0; i <= nSize * nSize / 64; i++) {
                    if (hostile[bP.row][bP.col][i]) {
                        for (unsigned long long j = 1ull; j; j = j << 1) {
                            if (hostile[bP.row][bP.col][i] & j) {
                                Pos cP = parent[count / nSize][count % nSize];
                                for (; cP != parent[cP.row][cP.col]; cP = parent[cP.row][cP.col]) {}
                                hostile[cP.row][cP.col][indexB / 64] &= ~(1ull << (indexB % 64));
                                hostile[cP.row][cP.col][indexBP / 64] |= (1ull << (indexBP % 64));
                            }
                            count++;
                        }
                    }
                    else {
                        count += 64;
                    }
                }

                parent[b.row][b.col] = aP;
                alliance[b.row][b.col]->next = alliance[aP.row][aP.col]->next;
                alliance[aP.row][aP.col]->next = alliance[b.row][b.col];
            }
            else {
                int count = 0;
                for (int i = 0; i <= nSize * nSize / 64; i++) {
                    if (hostile[b.row][b.col][i]) {
                        for (unsigned long long j = 1ull; j; j = j << 1) {
                            if (hostile[b.row][b.col][i] & j) {
                                Pos cP = parent[count / nSize][count % nSize];
                                for (; cP != parent[cP.row][cP.col]; cP = parent[cP.row][cP.col]) {}
                                hostile[cP.row][cP.col][indexB / 64] &= ~(1ull << (indexB % 64));
                            }
                            count++;
                        }
                    }
                    else {
                        count += 64;
                    }
                }

                parent[b.row][b.col] = aP;
                alliance[b.row][b.col]->next = alliance[aP.row][aP.col]->next;
                alliance[aP.row][aP.col]->next = alliance[b.row][b.col];
            }
            alliance[b.row][b.col] = nullptr;
        }

        return 1;
    }
    else {
        soldier[b.row][b.col] = defenseCount - attackCount;

        return 0;
    }
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
    Pos pos = trie.find(mMonarch);
    int sum = 0;
    if (mOption == 0) {
        soldier[pos.row][pos.col] += mNum;
        sum = soldier[pos.row][pos.col];
    }
    else {
        for (; pos != parent[pos.row][pos.col]; pos = parent[pos.row][pos.col]) {}
        for (List* allyList = alliance[pos.row][pos.col]; allyList; allyList = allyList->next) {
            Pos cur = allyList->data;
            soldier[cur.row][cur.col] += mNum;
            sum += soldier[cur.row][cur.col];
        }
    }

    return sum;
}