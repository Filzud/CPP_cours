#include <iostream>
#include <string>
using namespace std;

struct Date { int d, m, y; };
struct Student { string fio; Date dob; int marks[5]; };
void printStudent(const Student& s) 
{
    cout << s.fio << " | "
        << (s.dob.d < 10 ? "0" : "") << s.dob.d << "."
        << (s.dob.m < 10 ? "0" : "") << s.dob.m << "."
        << s.dob.y << " | ";
    for (int i = 0; i < 5; ++i) {
        cout << s.marks[i];
        if (i < 4) cout << " ";
    }
    cout << "\n";
}
double getAverageRating(const Student& s)
{
    double sum = 0; for (int i = 0; i < 5; ++i) sum += s.marks[i];
    return sum / 5.0;
}

int main() 
{
    setlocale(LC_ALL, "rus");
    Student g[4] = {
        {"Иванов Денис", {1,1,2003}, {5,4,4,5,5}},
        {"Филипов Филипп", {12,5,2002}, {3,4,5,4,4}},
        {"Иванова Анна", {23,9,2003}, {5,5,5,4,5}},
        {"Решала Антон", {7,3,2004}, {4,4,3,4,5}}
    };

    cout << "All:\n"; for (int i = 0; i < 4; ++i) printStudent(g[i]);
    cout << "\nAvg > 4.0:\n";
    for (int i = 0; i < 4; ++i) if (getAverageRating(g[i]) > 4.0)
        cout << g[i].fio << " (" << getAverageRating(g[i]) << ")\n";
    return 0;
}
