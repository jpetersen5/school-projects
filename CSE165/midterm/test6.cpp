#include <iostream>
using namespace std;

int x, y;
int *px, *py;

int f(int a, int b) {
    static int s = *px + *py;
    cout << s << endl;
    x = a + s; y = b + s;
    a = x;
    b = y;
    s = x - y;
    cout << s << endl;
    return s;
}

int main() {
    x = y = 1;
    int a = 2, b = 2;
    px = &x; py = &y;
    x = f(a,b);
    b = f(a,b);
    cout << *px << endl;
    cout << *py << endl;
    return 0;
}