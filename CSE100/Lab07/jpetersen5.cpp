#include <iostream>
using namespace std;


void cutRod(int* p, int n);


int main() {
        // initial variables
        int* prices;
        int sz, i;

        // input
        cin >> sz;
        prices = new int[sz];

        for (i = 0; i < sz; i++)
                cin >> prices[i];

        cutRod(prices, sz);

        return 0;
}


void cutRod(int* p, int n) {
        int* r = new int[n + 1];
        int* s = new int[n + 1];
        int i, j, q;

        r[0] = 0;

        for (j = 1; j <= n; j++) {
                q = -2147483648;
                for (i = 1; i <= j; i++) {
                        if (q < (p[i-1] + r[j - i])) {
                                q = p[i-1] + r[j - i];
                                s[j] = i;
                        }
                }
                r[j] = q;
        }

        cout << r[n] << endl;
        while (n > 0) {
                cout << s[n] << " ";
                n = n - s[n];
        }
        cout << "-1" << endl;
}