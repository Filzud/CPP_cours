#ifndef BAZADANNYH_H
#define BAZADANNYH_H

#include <string>
#include <sqlite3.h>

using namespace std;

class BazaDannyh {
private:
    sqlite3* bd;  // указатель на БД
    string put;  // путь к файлу БД

public:
    BazaDannyh();  // конструктор
    ~BazaDannyh();  // деструктор
    bool inicializovat(const string& imjaFajla);  // инициализация БД
    void zakryt();  // закрыть БД
    sqlite3* poluchitUkazatel();  // получить указатель
};

#endif
