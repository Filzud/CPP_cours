#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string address;
public:
    Person(string n, int a, string addr) :name(n), age(a), address(addr) {}
    virtual void displayInfo() const {
        cout << name << ", " << age << ", " << address << endl;
    }
    virtual ~Person() {}
};

class Student : public Person {
private:
    string studentId;
    double averageGrade;
public:
    Student(string n, int a, string addr, string id, double avg) :Person(n, a, addr), studentId(id), averageGrade(avg) {}
    void displayInfo() const override {
        cout << name << ", " << age << ", " << address << ", " << studentId << ", avg=" << averageGrade << endl;
    }
    void setAverage(double v) { if (v >= 0) averageGrade = v; }
    double getAverage() const { return averageGrade; }
};

class Professor : public Person {
private:
    string department;
    double salary;
    int yearsOfExperience;
public:
    Professor(string n, int a, string addr, string dep, double sal, int y) :Person(n, a, addr), department(dep), salary(sal), yearsOfExperience(y) {}
    void displayInfo() const override {
        cout << name << ", " << age << ", " << address << ", " << department << ", " << salary << ", " << yearsOfExperience << endl;
    }
    double allowance() const { return salary * 0.01 * yearsOfExperience; }
};

int main() 
{
    setlocale(LC_ALL, "rus");
    Student st("Петр Петров", 20, "ул. Студенческая, 20", "S12345", 4.3);
    Professor pr("Доктор Лужников", 45, "ул. Академическая, 10", "С++", 50000, 15);
    st.displayInfo();
    pr.displayInfo();
    return 0;
}
