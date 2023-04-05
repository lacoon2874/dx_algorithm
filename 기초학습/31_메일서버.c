#define USER_MAX 1000
#define MAIL_MAX 310
#define WORD_MAX 10

struct Element {
    unsigned long long word[WORD_MAX];
    int wordCount;
};

Element mail[USER_MAX][MAIL_MAX];
int front[USER_MAX], back[USER_MAX];
int count[USER_MAX];
int nSize, kSize;

void init(int N, int K) {
    nSize = N;
    kSize = K;
    for (int i = 0; i < nSize; i++) {
        front[i] = 0;
        back[i] = 0;
        count[i] = 0;
    }
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    int index = 0, wordCount = 0;
    unsigned long long word[10];
    while (wordCount < 10) {
        word[wordCount] = 0ull;
        for (; subject[index] != ' ' && subject[index] != '\0'; index++) {
            word[wordCount] = (word[wordCount] << 5) + (subject[index] - 'a');
        }
        wordCount++;
        if (subject[index] == '\0') {
            break;
        }
        index++;
    }

    for (int i = 0; i < cnt; i++) {
        int cur = rIDs[i];
        if (count[cur] == kSize) {
            front[cur] = (front[cur] + 1) % MAIL_MAX;
            count[cur]--;
        }

        mail[cur][back[cur]].wordCount = wordCount;
        for (int j = 0; j < wordCount; j++) {
            mail[cur][back[cur]].word[j] = word[j];
        }
        back[cur] = (back[cur] + 1) % MAIL_MAX;

        count[cur]++;
    }
}

int getCount(int uID) {
    return count[uID];
}

int deleteMail(int uID, char subject[]) {
    int index = 0, wordCount = 0;
    unsigned long long word[10];
    while (wordCount < 10) {
        word[wordCount] = 0ull;
        for (; subject[index] != ' ' && subject[index] != '\0'; index++) {
            word[wordCount] = (word[wordCount] << 5) + (subject[index] - 'a');
        }
        wordCount++;
        if (subject[index] == '\0') {
            break;
        }
        index++;
    }

    int answer = 0;
    int pos = front[uID];
    for (int i = front[uID]; i != back[uID]; i = (i + 1) % MAIL_MAX) {
        bool same = false;
        if (mail[uID][i].wordCount == wordCount) {
            same = true;
            for (int j = 0; j < mail[uID][i].wordCount; j++) {
                if (mail[uID][i].word[j] != word[j]) {
                    same = false;
                    break;
                }
            }
        }
        if (!same) {
            mail[uID][pos] = mail[uID][i];
            pos = (pos + 1) % MAIL_MAX;
        }
        else {
            answer++;
            count[uID]--;
        }
    }
    back[uID] = (front[uID] + count[uID]) % MAIL_MAX;

    return answer;
}

int searchMail(int uID, char text[]) {
    unsigned long long word = 0ull;
    for (int i = 0; text[i] != '\0'; i++) {
        word = (word << 5) + (text[i] - 'a');
    }

    int count = 0;
    for (int i = front[uID]; i != back[uID]; i = (i + 1) % MAIL_MAX) {
        for (int j = 0; j < mail[uID][i].wordCount; j++) {
            if (mail[uID][i].word[j] == word) {
                count++;
                break;
            }
        }
    }

    return count;
}