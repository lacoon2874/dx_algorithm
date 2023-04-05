#include <stack>
#include <vector>

#define MAX_LEN 200
#define MAX_SIZE 5001

struct Expr {
    int aa, bb, cc, ab, bc, ac, a, b, c, n;

    Expr() {}
    Expr(int ai, int bi, int ci, int ni) : aa(0), bb(0), cc(0), ab(0), bc(0), ac(0), a(ai), b(bi), c(ci), n(ni) {}

    void operator+=(const Expr& e) {
        this->aa += e.aa;
        this->bb += e.bb;
        this->cc += e.cc;
        this->ab += e.ab;
        this->bc += e.bc;
        this->ac += e.ac;
        this->a += e.a;
        this->b += e.b;
        this->c += e.c;
        this->n += e.n;
    }

    void operator-=(const Expr& e) {
        this->aa -= e.aa;
        this->bb -= e.bb;
        this->cc -= e.cc;
        this->ab -= e.ab;
        this->bc -= e.bc;
        this->ac -= e.ac;
        this->a -= e.a;
        this->b -= e.b;
        this->c -= e.c;
        this->n -= e.n;
    }

    void operator*=(const Expr& e) {
        this->aa = this->a * e.a;
        this->bb = this->b * e.b;
        this->cc = this->c * e.c;
        this->ab = this->a * e.b + this->b * e.a;
        this->bc = this->b * e.c + this->c * e.b;
        this->ac = this->a * e.c + this->c * e.a;
        this->a = this->a * e.n + this->n * e.a;
        this->b = this->b * e.n + this->n * e.b;
        this->c = this->c * e.n + this->n * e.c;
        this->n = this->n * e.n;
    }

    bool operator==(const Expr& e) const {
        if (this->aa == e.aa && this->bb == e.bb && this->cc == e.cc
            && this->ab == e.ab && this->bc == e.bc && this->ac == e.ac
            && this->a == e.a && this->b == e.b && this->c == e.c && this->n == e.n) {
            return true;
        }
        return false;
    }
};

Expr expr[MAX_SIZE];
std::vector<std::vector<int>> arr[4];

void init()
{
    for (int i = 0; i < 4; i++) {
        arr[i].clear();
    }
}

int addExpression(int mID, char mExpression[MAX_LEN + 1])
{
    std::stack<Expr> eStk;
    std::stack<char> opStk;

    for (int i = 0; mExpression[i] != '\0'; i++) {
        if (mExpression[i] >= '1' && mExpression[i] <= '5') {
            eStk.emplace(0, 0, 0, mExpression[i] - '0');
        }
        else if (mExpression[i] == 'A') {
            eStk.emplace(1, 0, 0, 0);
        }
        else if (mExpression[i] == 'B') {
            eStk.emplace(0, 1, 0, 0);
        }
        else if (mExpression[i] == 'C') {
            eStk.emplace(0, 0, 1, 0);
        }
        else {
            switch (mExpression[i]) {
            case '(':
            case '*':
                opStk.push(mExpression[i]);
                break;
            case '+':
            case '-':
                while (!opStk.empty() && opStk.top() != '(') {
                    Expr b = eStk.top();
                    eStk.pop();
                    Expr a = eStk.top();
                    eStk.pop();

                    if (opStk.top() == '+') {
                        a += b;
                    }
                    else if (opStk.top() == '-') {
                        a -= b;
                    }
                    else {
                        a *= b;
                    }
                    eStk.push(a);
                    opStk.pop();
                }
                opStk.push(mExpression[i]);
                break;
            case ')':
                while (opStk.top() != '(') {
                    Expr b = eStk.top();
                    eStk.pop();
                    Expr a = eStk.top();
                    eStk.pop();

                    if (opStk.top() == '+') {
                        a += b;
                    }
                    else if (opStk.top() == '-') {
                        a -= b;
                    }
                    else {
                        a *= b;
                    }
                    eStk.push(a);
                    opStk.pop();
                }
                opStk.pop();
                break;
            }
        }
    }
    while (!opStk.empty()) {
        Expr b = eStk.top();
        eStk.pop();
        Expr a = eStk.top();
        eStk.pop();

        if (opStk.top() == '+') {
            a += b;
        }
        else if (opStk.top() == '-') {
            a -= b;
        }
        else {
            a *= b;
        }
        eStk.push(a);
        opStk.pop();
    }

    expr[mID] = eStk.top();
    int count = 0;
    bool has[3];
    for (int i = 0; i < 3; i++) {
        has[i] = false;
    }
    if (expr[mID].aa || expr[mID].ab || expr[mID].ac || expr[mID].a) {
        has[0] = true;
    }
    if (expr[mID].bb || expr[mID].ab || expr[mID].bc || expr[mID].b) {
        has[1] = true;
    }
    if (expr[mID].cc || expr[mID].bc || expr[mID].ac || expr[mID].c) {
        has[2] = true;
    }
    for (int i = 0; i < 3; i++) {
        if (has[i]) {
            count++;
        }
    }

    for (size_t i = 0; i < arr[count].size(); i++) {
        if (expr[arr[count][i][0]] == expr[mID]) {
            arr[count][i].push_back(mID);
            return static_cast<int>(arr[count][i].size() - 1);
        }
    }
    arr[count].emplace_back(std::vector<int>(1, mID));
    return -count;
}

int calcExpression(int mID, int mA, int mB, int mC)
{
    int sum = 0;

    sum += (mA * mA * expr[mID].aa);
    sum += (mB * mB * expr[mID].bb);
    sum += (mC * mC * expr[mID].cc);
    sum += (mA * mB * expr[mID].ab);
    sum += (mB * mC * expr[mID].bc);
    sum += (mA * mC * expr[mID].ac);
    sum += (mA * expr[mID].a);
    sum += (mB * expr[mID].b);
    sum += (mC * expr[mID].c);
    sum += expr[mID].n;

    return sum;
}