#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name; int age;
public:
    Person(string n, int a) :name(n), age(a) {}
    virtual void display() const { cout << name << ", " << age << endl; }
    virtual ~Person() {}
};

class Employee {
protected:
    string position; double salary;
public:
    Employee(string p, double s) :position(p), salary(s) {}
    virtual void work() const { cout << "Работает" << endl; }
    virtual ~Employee() {}
};

class Teacher : public Person, public Employee {
private:
    string subject; int experienceYears;
public:
    Teacher(string n, int a, string p, double s, string subj, int y) :Person(n, a), Employee(p, s), subject(subj), experienceYears(y) {}
    void display() const override { cout << name << ", " << age << ", " << position << ", " << salary << ", " << subject << ", " << experienceYears << endl; }
    void work() const override { cout << "Преподает " << subject << endl; }
};

class Researcher {
protected:
    string researchArea; int publicationsCount;
public:
    Researcher(string area, int pubs) :researchArea(area), publicationsCount(pubs) {}
    void conductResearch() const { cout << "Исследует " << researchArea << endl; }
    virtual ~Researcher() {}
};

class Professor : public Teacher, public Researcher {
public:
    Professor(string n, int a, string p, double s, string subj, int y, string area, int pubs)
        :Teacher(n, a, p, s, subj, y), Researcher(area, pubs) {
    }
    void display() const override { Teacher::display(); cout << researchArea << ", " << publicationsCount << endl; }
    void work() const override { cout << "Руководит и преподает " << endl; }
};

int main() 
{
    setlocale(LC_ALL, "rus");
    Teacher t("Ирина", 35, "Teacher", 60000, "Math", 10);
    Professor pr("Андрей", 50, "Professor", 120000, "CS", 20, "AI", 100);
    t.display(); t.work();
    pr.display(); pr.work(); pr.conductResearch();
    return 0;
}
