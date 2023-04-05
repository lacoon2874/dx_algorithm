#include<iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        string input;
        cin >> input;

        long long bCount[16], cCount[16];
        for (int i = 0; i < 16; i++) {
            bCount[i] = 0;
            cCount[i] = 0;
        }
        bCount[0] = 1;

        unsigned long long before = 1ull;
        for (size_t i = 0; i < input.length(); i++) {
            unsigned long long charge = 1ull << (input[i] - 'A'), cur = 0ull;
            for (int index = 0; before; index++) {
                unsigned long long temp = before & 15ull;
                if (temp != 0ull) {
                    unsigned long long temp2 = 0ull;
                    for (unsigned long long j = 1ull; j < 16ull; j++) {
                        if ((j & charge) != 0ull && (j & temp) != 0ull) {
                            temp2 |= (j << (4 * j));
                            cCount[j] += bCount[index];
                        }
                    }
                    cur |= temp2;
                }
                before = before >> 4;
            }
            before = cur;
            for (int j = 1; j < 16; j++) {
                bCount[j] = cCount[j] % 1000000007;
                cCount[j] = 0;
            }
        }

        long long answer = 0;
        for (int i = 1; i < 16; i++) {
            answer = (answer + bCount[i]) % 1000000007;
        }

        cout << '#' << test_case << ' ' << answer << endl;
    }

    return 0;
}