#include <iostream>
using namespace std;

int main() 
{
    const int n = 10;
    int a[n], b[n];
    int* p = a;
    *p = 0;
    *(p + 1) = 1;
    for (int i = 2; i < n; ++i) *(p + i) = *(p + i - 1) + *(p + i - 2);
    long long sum = 0;
    int* q = a;
    int* end = a + n;
    while (q < end) { sum += *q; ++q; }
    int mn = *a;
    q = a + 1;
    while (q < end) { if (*q < mn) mn = *q; ++q; }
    const int* src = a + n - 1;
    int* dst = b;
    for (int i = 0; i < n; ++i) { *dst = *src; ++dst; --src; }
    cout << "A: ";
    q = a; end = a + n;
    while (q < end) { cout << *q << (q + 1 < end ? ' ' : '\n'); ++q; }
    cout << "sum(A): " << sum << "\n";
    cout << "min(A): " << mn << "\n";
    cout << "B (rev A): ";
    q = b; end = b + n;
    while (q < end) { cout << *q << (q + 1 < end ? ' ' : '\n'); ++q; }

    return 0;
}
