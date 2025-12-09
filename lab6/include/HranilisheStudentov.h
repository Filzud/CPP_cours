#ifndef HRANILISHESTUDENTOV_H
#define HRANILISHESTUDENTOV_H

#include <string>
#include <vector>
#include <optional>
#include <sqlite3.h>

using namespace std;

struct Uchenik {  // структура ученика
    int id;  // ID
    string imja;  // имя
    string pochta;  // email
    string gruppa;  // группа
};

struct Ocenka {  // структура оценки
    string predmet;  // предмет
    int ball;  // балл
};

struct UchenikSredBall {  // структура ученика со средним баллом
    int id;  // ID
    string imja;  // имя
    double srednijBall;  // средний балл
};

class HranilisheStudentov {
private:
    sqlite3* bd;  // указатель на БД

public:
    HranilisheStudentov(sqlite3* baza);  // конструктор
    bool dobavitStudenta(const string& imja, const string& pochta, const string& gruppa);  // добавить студента
    optional<Uchenik> poluchitStudenta(int id);  // получить студента
    bool obnovitStudenta(int id, const string& imja, const string& pochta, const string& gruppa);  // обновить
    bool udalitStudenta(int id);  // удалить
    vector<Uchenik> vseStudenty();  // все студенты
    bool dobavitOcenku(int studentId, const string& predmet, int ball);  // добавить оценку
    bool dobavitStudentaSocenkami(const string& imja, const string& pochta, const string& gruppa, const vector<Ocenka>& ocenki);  // добавить с оценками
    vector<Uchenik> studentyGruppy(const string& gruppa);  // студенты по группе
    double srednjajaOcenka(const string& predmet);  // средняя оценка
    vector<UchenikSredBall> luchshieStudenty(int limit);  // лучшие студенты
    bool paketVstavka(const vector<Uchenik>& studenty);  // пакетная вставка
};

#endif
