#ifndef STUDENTREPOSITORY_H
#define STUDENTREPOSITORY_H

#include <optional>
#include <string>
#include <vector>
#include <sqlite3.h>

#include "InputValidator.h"

using namespace std;

struct Student {
    int id;
    string name;
    string email;
    string groupName;
};

struct Grade {
    string subject;
    int grade;
};

class StudentRepository {
private:
    sqlite3* db;
    const InputValidator& validator;

    bool execSimple(const char* sql);

public:
    StudentRepository(sqlite3* dbHandle, const InputValidator& v);

    bool addStudent(const string& name, const string& email, const string& group);
    optional<Student> getStudent(int id);
    bool updateStudent(int id, const string& newName, const string& newEmail, const string& newGroup);
    bool deleteStudent(int id);
    vector<Student> getAllStudents();

    bool addStudentWithGrades(const string& name, const string& email, const string& group, const vector<Grade>& grades);
    vector<Student> getStudentsByGroup(const string& group);
    optional<double> getAverageGradeBySubject(const string& subject);
    vector<pair<Student, double>> getTopStudents(int limit);
    bool batchInsertStudents(const vector<Student>& students);
};

#endif
