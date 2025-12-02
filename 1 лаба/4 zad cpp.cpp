#include <iostream>
using namespace std;

void swapByValue(int a, int b) 
{
    int t = a;
    a = b;
    b = t;
}
void swapByPointer(int* a, int* b) 
{
    if (!a || !b) return;
    int t = *a;
    *a = *b;
    *b = t;
}

void swapByReference(int& a, int& b) 
{
    int t = a;
    a = b;
    b = t;
}

int main() 
{
    int x = 5, y = 10;
    cout << "Before: x=" << x << " y=" << y << "\n";
    swapByValue(x, y);
    cout << "After swapByValue: x=" << x << " y=" << y << " (no change)\n";
    swapByPointer(&x, &y);
    cout << "After swapByPointer: x=" << x << " y=" << y << "\n";
    swapByReference(x, y);
    cout << "After swapByReference: x=" << x << " y=" << y << "\n";

    return 0;
}
