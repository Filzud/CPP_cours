#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <sqlite3.h>

using namespace std;

class DatabaseManager {
private:
    sqlite3* db;
    string path;

    bool execSimple(const char* sql);

public:
    DatabaseManager();
    ~DatabaseManager();

    bool initialize(const string& filePath);
    void close();
    sqlite3* getHandle();
};

#endif
