#include "DatabaseManager.h"
#include <iostream>

using namespace std;

DatabaseManager::DatabaseManager() : db(nullptr) {}

DatabaseManager::~DatabaseManager() { close(); }

bool DatabaseManager::execSimple(const char* sql) {
    char* err = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        cerr << "SQLite error: " << (err ? err : "unknown") << endl;
        if (err) sqlite3_free(err);
        return false;
    }
    return true;
}

bool DatabaseManager::initialize(const string& filePath) {
    path = filePath;
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        cerr << "Failed to open DB: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Pragmas for integrity/performance
    execSimple("PRAGMA foreign_keys = ON;");
    execSimple("PRAGMA synchronous = NORMAL;");
    execSimple("PRAGMA journal_mode = WAL;");

    // Create tables
    const char* studentsSql =
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "email TEXT UNIQUE, "
        "group_name TEXT);";
    if (!execSimple(studentsSql)) return false;

    const char* gradesSql =
        "CREATE TABLE IF NOT EXISTS grades ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "student_id INTEGER, "
        "subject TEXT, "
        "grade INTEGER, "
        "FOREIGN KEY(student_id) REFERENCES students(id) ON DELETE CASCADE);";
    if (!execSimple(gradesSql)) return false;

    // Indexes
    execSimple("CREATE INDEX IF NOT EXISTS idx_students_email ON students(email);");
    execSimple("CREATE INDEX IF NOT EXISTS idx_students_group ON students(group_name);");
    execSimple("CREATE INDEX IF NOT EXISTS idx_grades_subject ON grades(subject);");

    return true;
}

void DatabaseManager::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

sqlite3* DatabaseManager::getHandle() { return db; }
