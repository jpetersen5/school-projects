#include <iostream>
using namespace std;

int x, y;
int *px, *py;

int f() {
    static int s = *px + *py;
    cout << s << endl;
    return s;
}

int main() {
    x = y = 2;
    px = &x; py = &y;
    x = y = f();
    cout << f() << endl;
}