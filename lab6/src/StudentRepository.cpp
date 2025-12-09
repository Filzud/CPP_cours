#include "StudentRepository.h"
#include <iostream>

using namespace std;

StudentRepository::StudentRepository(sqlite3* dbHandle, const InputValidator& v)
    : db(dbHandle), validator(v) {}

bool StudentRepository::execSimple(const char* sql) {
    char* err = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        cerr << "SQLite error: " << (err ? err : "unknown") << endl;
        if (err) sqlite3_free(err);
        return false;
    }
    return true;
}

bool StudentRepository::addStudent(const string& name, const string& email, const string& group) {
    if (!validator.isValidEmail(email) || !validator.isSafeInput(name) || !validator.isSafeInput(group) ||
        !validator.isValidLength(name, 2, 100) || !validator.isValidLength(group, 2, 50)) {
        cerr << "Validation failed for student data\n";
        return false;
    }

    const char* sql = "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, group.c_str(), -1, SQLITE_TRANSIENT);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    if (!ok) cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
    sqlite3_finalize(stmt);
    return ok;
}

optional<Student> StudentRepository::getStudent(int id) {
    const char* sql = "SELECT id, name, email, group_name FROM students WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return nullopt;
    }
    sqlite3_bind_int(stmt, 1, id);

    optional<Student> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Student s;
        s.id = sqlite3_column_int(stmt, 0);
        s.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        s.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        s.groupName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        result = s;
    }
    sqlite3_finalize(stmt);
    return result;
}

bool StudentRepository::updateStudent(int id, const string& newName, const string& newEmail, const string& newGroup) {
    if (!validator.isValidEmail(newEmail) || !validator.isSafeInput(newName) || !validator.isSafeInput(newGroup) ||
        !validator.isValidLength(newName, 2, 100) || !validator.isValidLength(newGroup, 2, 50)) {
        cerr << "Validation failed for update\n";
        return false;
    }

    const char* sql = "UPDATE students SET name = ?, email = ?, group_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, newEmail.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, newGroup.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, id);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    if (!ok) cerr << "Update failed: " << sqlite3_errmsg(db) << endl;
    sqlite3_finalize(stmt);
    return ok;
}

bool StudentRepository::deleteStudent(int id) {
    const char* sql = "DELETE FROM students WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    if (!ok) cerr << "Delete failed: " << sqlite3_errmsg(db) << endl;
    sqlite3_finalize(stmt);
    return ok;
}

vector<Student> StudentRepository::getAllStudents() {
    vector<Student> out;
    const char* sql = "SELECT id, name, email, group_name FROM students;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return out;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Student s;
        s.id = sqlite3_column_int(stmt, 0);
        s.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        s.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        s.groupName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        out.push_back(s);
    }
    sqlite3_finalize(stmt);
    return out;
}

bool StudentRepository::addStudentWithGrades(const string& name, const string& email, const string& group, const vector<Grade>& grades) {
    // Basic validation
    if (!validator.isValidEmail(email) || !validator.isSafeInput(name) || !validator.isSafeInput(group) ||
        !validator.isValidLength(name, 2, 100) || !validator.isValidLength(group, 2, 50)) {
        cerr << "Validation failed for student data\n";
        return false;
    }
    for (const auto& g : grades) {
        if (!validator.isSafeInput(g.subject) || !validator.isValidLength(g.subject, 1, 100) || !validator.isValidGrade(g.grade)) {
            cerr << "Validation failed for grade data\n";
            return false;
        }
    }

    if (!execSimple("BEGIN;")) return false;

    // Insert student
    const char* studentSql = "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";
    sqlite3_stmt* studentStmt = nullptr;
    if (sqlite3_prepare_v2(db, studentSql, -1, &studentStmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        execSimple("ROLLBACK;");
        return false;
    }
    sqlite3_bind_text(studentStmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(studentStmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(studentStmt, 3, group.c_str(), -1, SQLITE_TRANSIENT);

    bool ok = sqlite3_step(studentStmt) == SQLITE_DONE;
    if (!ok) {
        cerr << "Insert student failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(studentStmt);
        execSimple("ROLLBACK;");
        return false;
    }
    sqlite3_finalize(studentStmt);

    int studentId = static_cast<int>(sqlite3_last_insert_rowid(db));

    // Insert grades
    const char* gradeSql = "INSERT INTO grades (student_id, subject, grade) VALUES (?, ?, ?);";
    sqlite3_stmt* gradeStmt = nullptr;
    if (sqlite3_prepare_v2(db, gradeSql, -1, &gradeStmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        execSimple("ROLLBACK;");
        return false;
    }
    for (const auto& g : grades) {
        sqlite3_bind_int(gradeStmt, 1, studentId);
        sqlite3_bind_text(gradeStmt, 2, g.subject.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(gradeStmt, 3, g.grade);
        ok = sqlite3_step(gradeStmt) == SQLITE_DONE;
        if (!ok) {
            cerr << "Insert grade failed: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(gradeStmt);
            execSimple("ROLLBACK;");
            return false;
        }
        sqlite3_reset(gradeStmt);
        sqlite3_clear_bindings(gradeStmt);
    }
    sqlite3_finalize(gradeStmt);

    if (!execSimple("COMMIT;")) {
        execSimple("ROLLBACK;");
        return false;
    }
    return true;
}

vector<Student> StudentRepository::getStudentsByGroup(const string& group) {
    vector<Student> out;
    const char* sql = "SELECT id, name, email, group_name FROM students WHERE group_name = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return out;
    }
    sqlite3_bind_text(stmt, 1, group.c_str(), -1, SQLITE_TRANSIENT);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Student s;
        s.id = sqlite3_column_int(stmt, 0);
        s.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        s.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        s.groupName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        out.push_back(s);
    }
    sqlite3_finalize(stmt);
    return out;
}

optional<double> StudentRepository::getAverageGradeBySubject(const string& subject) {
    const char* sql = "SELECT AVG(grade) FROM grades WHERE subject = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return nullopt;
    }
    sqlite3_bind_text(stmt, 1, subject.c_str(), -1, SQLITE_TRANSIENT);
    optional<double> avg;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        if (sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
            avg = sqlite3_column_double(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return avg;
}

vector<pair<Student, double>> StudentRepository::getTopStudents(int limit) {
    vector<pair<Student, double>> out;
    const char* sql =
        "SELECT s.id, s.name, s.email, s.group_name, AVG(g.grade) as avg_grade "
        "FROM students s "
        "JOIN grades g ON s.id = g.student_id "
        "GROUP BY s.id, s.name, s.email, s.group_name "
        "ORDER BY avg_grade DESC "
        "LIMIT ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return out;
    }
    sqlite3_bind_int(stmt, 1, limit);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Student s;
        s.id = sqlite3_column_int(stmt, 0);
        s.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        s.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        s.groupName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        double avg = sqlite3_column_double(stmt, 4);
        out.push_back({s, avg});
    }
    sqlite3_finalize(stmt);
    return out;
}

bool StudentRepository::batchInsertStudents(const vector<Student>& students) {
    if (!execSimple("BEGIN;")) return false;

    const char* sql = "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        execSimple("ROLLBACK;");
        return false;
    }

    bool ok = true;
    for (const auto& s : students) {
        if (!validator.isValidEmail(s.email) || !validator.isSafeInput(s.name) || !validator.isSafeInput(s.groupName) ||
            !validator.isValidLength(s.name, 2, 100) || !validator.isValidLength(s.groupName, 2, 50)) {
            cerr << "Validation failed for batch insert\n";
            ok = false;
            break;
        }
        sqlite3_bind_text(stmt, 1, s.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, s.email.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, s.groupName.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Batch insert failed: " << sqlite3_errmsg(db) << endl;
            ok = false;
            break;
        }
        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);
    }
    sqlite3_finalize(stmt);

    if (ok) {
        if (!execSimple("COMMIT;")) {
            execSimple("ROLLBACK;");
            return false;
        }
    } else {
        execSimple("ROLLBACK;");
    }
    return ok;
}
