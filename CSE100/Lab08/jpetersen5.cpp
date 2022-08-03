#include <iostream>
using namespace std;

void matrixChainOrder(int* p, int n);
void matrixOrderPrint(int** s, int i, int j);


int main() {
        // initial variables
        int numMat, i;
        int* dims;

        cin >> numMat;
        dims = new int[numMat + 1];

        for (i = 0; i <= numMat; i++)
                cin >> dims[i];

        matrixChainOrder(dims, numMat);

        return 0;
}


void matrixChainOrder(int* p, int n) {
        int** m;
        int** s;
        int i, j, k, l, q;

        m = new int*[n];
        s = new int*[n - 1];

        for (i = 0; i < n; i++) {
                m[i] = new int[n];
                m[i][i] = 0;

                if (i == n - 1)
                        continue;

                s[i] = new int[n - 1];
        }

        for (l = 2; l <= n; l++) {
                for (i = 1; i <= n - l + 1; i++) {
                        j = i + l - 1;
                        m[i-1][j-1] = 2147483647;
                        for (k = i; k < j; k++) {
                                q = m[i-1][k-1] + m[k + 1-1][j-1] + p[i-1] * p[k] * p[j];
                                //cout << "l = " << l << ";  i = " << i << ";  j = " << j << ";  k = " << k << endl;
                                //cout << "m[" << i-1 << "][" << j-1 << "] = " << q << " = " << m[i-1][k-1] << " + " << m[k + 1-1][j-1] << " + " << p[i-1] << "*" << p[k] << "*" << p[j] << endl;
                                if (q < m[i-1][j-1]) {
                                        m[i-1][j-1] = q;
                                        s[i-1][j - 1-1] = k-1;
                                }
                        }
                }
        }

        cout << m[0][n-1] << endl;
        matrixOrderPrint(s,0,n - 1);
        cout << endl;
}

void matrixOrderPrint(int** s, int i, int j) {
        if (i == j)
                cout << "A" << i;
        else {
                cout << "(";
                matrixOrderPrint(s,i,s[i][j-1]);
                matrixOrderPrint(s,s[i][j-1] + 1,j);
                cout << ")";
        }
}