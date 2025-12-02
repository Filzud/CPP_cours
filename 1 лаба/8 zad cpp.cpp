#include <iostream>
using namespace std;

void arrayInfo(const int* a, int n) 
{
    long long sum = 0;
    for (int i = 0; i < n; ++i) sum += a[i];
    cout << "Size: " << n << ", Sum: " << sum;
    if (n > 0) cout << ", First: " << a[0] << ", Last: " << a[n - 1];
    cout << "\n";
}

int main() 
{
    int a1[] = { 1,2,3,4 };
    int a2[] = { 10,-5,7,0,12,8 };
    arrayInfo(a1, 4);
    arrayInfo(a2, 6);
    return 0;
}
