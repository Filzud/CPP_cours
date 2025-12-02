#include <iostream>
using namespace std;

int main() 
{
    int N;
    cout << "Days: ";
    if (!(cin >> N) || N <= 0) return 0;

    double* t = new double[N];
    for (int i = 0; i < N; ++i) 
    {
        cout << "t[" << i << "]: ";
        cin >> t[i];
    }

    double sum = 0.0, mn = t[0], mx = t[0];
    for (int i = 0; i < N; ++i) 
    {
        sum += t[i];
        if (t[i] < mn) mn = t[i];
        if (t[i] > mx) mx = t[i];
    }
    double avg = sum / N;
    int below = 0;
    for (int i = 0; i < N; ++i) if (t[i] < avg) ++below;
    cout.setf(ios::fixed); cout.precision(2);
    cout << "Average: " << avg << "\n";
    cout << "Min: " << mn << "\n";
    cout << "Max: " << mx << "\n";
    cout << "Below average days: " << below << "\n";
    delete[] t;
    return 0;
}
