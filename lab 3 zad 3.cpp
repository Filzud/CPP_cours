#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class UniversityMember {
protected:
    string name, id, email;
public:
    UniversityMember(string n, string i, string e) : name(n), id(i), email(e) {}
    virtual ~UniversityMember() {}
    virtual void displayInfo() const = 0;
    virtual void work() const = 0;
    virtual string getRole() const = 0;
    string getName() const { return name; }
    string getId() const { return id; }
};

class Student : public UniversityMember {
private:
    string major;
    int year;
    double gpa;
    vector<string> courses;
public:
    Student(string n, string i, string e, string m, int y, double g)
        : UniversityMember(n, i, e), major(m), year(y), gpa(g) {
    }
    void enrollCourse(const string& c) { courses.push_back(c); }
    void dropCourse(const string& c) { auto it = find(courses.begin(), courses.end(), c); if (it != courses.end()) courses.erase(it); }
    void displayInfo() const override {
        cout << "Student: " << name << ", " << id << ", " << email << ", " << major << ", " << year << ", " << gpa << endl;
    }
    void work() const override { cout << "Учится" << endl; }
    string getRole() const override { return "Student"; }
};

class Professor : public UniversityMember {
private:
    string department, office;
    double salary;
    vector<string> teachingCourses;
public:
    Professor(string n, string i, string e, string d, string o, double s)
        : UniversityMember(n, i, e), department(d), office(o), salary(s) {
    }
    void assignCourse(const string& c) { teachingCourses.push_back(c); }
    void removeCourse(const string& c) { auto it = find(teachingCourses.begin(), teachingCourses.end(), c); if (it != teachingCourses.end()) teachingCourses.erase(it); }
    double calculateSalary() const { return salary; }
    void displayInfo() const override {
        cout << "Professor: " << name << ", " << id << ", " << email << ", " << department << ", " << office << ", " << salary << endl;
    }
    void work() const override { cout << "Преподает" << endl; }
    string getRole() const override { return "Professor"; }
};

class Course {
private:
    string courseCode, courseName;
    int credits;
    Professor* instructor;
    vector<Student*> enrolled;
public:
    Course(string c, string n, int cr) : courseCode(c), courseName(n), credits(cr), instructor(nullptr) {}
    void setInstructor(Professor* p) { instructor = p; }
    void addStudent(Student* s) { enrolled.push_back(s); }
    void removeStudentByName(const string& n) {
        auto it = remove_if(enrolled.begin(), enrolled.end(), [&](Student* s) { return s->getName() == n; });
        enrolled.erase(it, enrolled.end());
    }
    void displayCourseInfo() const {
        cout << courseCode << ", " << courseName << ", " << credits << endl;
        if (instructor) cout << "Преподаватель: " << instructor->getName() << endl;
        cout << "Студентов: " << enrolled.size() << endl;
    }
};

class University {
private:
    string name;
    vector<unique_ptr<UniversityMember>> members;
    vector<unique_ptr<Course>> courses;
    static int totalUniversities;
public:
    University(string n) : name(n) { totalUniversities++; }
    ~University() { totalUniversities--; }
    void addMember(unique_ptr<UniversityMember> m) { members.push_back(move(m)); }
    void addCourse(unique_ptr<Course> c) { courses.push_back(move(c)); }
    static int getTotalUniversities() { return totalUniversities; }
    void display() const {
        cout << name << ", members=" << members.size() << ", courses=" << courses.size() << endl;
    }
};
int University::totalUniversities = 0;

int main() 
{
    setlocale(LC_ALL, "rus");
    University u("Tech");

    auto s = make_unique<Student>("Иван", "S1", "s1@mail", "CS", 1, 4.5);
    auto p = make_unique<Professor>("Анна", "P1", "p1@mail", "CS", "A-101", 120000);
    auto c = make_unique<Course>("CS101", "Intro", 4);

    Student* sptr = s.get();
    Professor* pptr = p.get();
    Course* cptr = c.get();

    cptr->setInstructor(pptr);
    cptr->addStudent(sptr);
    cptr->displayCourseInfo();

    u.addMember(move(s));
    u.addMember(move(p));
    u.addCourse(move(c));
    u.display();

    return 0;
}
