#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    int grades[5];
public:
    Student(string n, int a) : name(n), age(a) {
        for (int i = 0; i < 5; i++) grades[i] = 0;
    }
    string getName() const { return name; }
    int getAge() const { return age; }
    void setName(const string& n) { name = n; }
    void setAge(int a) { if (a >= 0) age = a; }
    void setGrade(int i, int g) { if (i >= 0 && i < 5 && g >= 0 && g <= 5) grades[i] = g; }
    double average() const {
        int s = 0; for (int i = 0; i < 5; i++) s += grades[i];
        return s / 5.0;
    }
    void displayInfo() const {
        cout << name << ", " << age << ", avg=" << average() << endl;
    }
    bool hasScholarship() const { return average() >= 4.5; }
};

int main() 
{
    setlocale(LC_ALL,"rus");
    Student s("Филипп Иванов", 21);
    s.setGrade(0, 5); s.setGrade(1, 4); s.setGrade(2, 5); s.setGrade(3, 3); s.setGrade(4, 4);
    s.displayInfo();
    cout << (s.hasScholarship() ? "Студент получает стипендию" : "Стипендия не положена)") << endl;
    return 0;
}
