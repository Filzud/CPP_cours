#ifndef PROVERKA_H
#define PROVERKA_H

#include <string>
#include <regex>

using namespace std;

class Proverka {
public:
    static bool validnajaPochta(const string& pochta);  // проверка email
    static bool bezopasnyjVvod(const string& tekst);  // проверка на SQL-инъекции
    static bool validnajaDlina(const string& imja);  // проверка длины имени
    static bool validnyjBall(int ball);  // проверка диапазона оценки
    static bool validnajaGruppa(const string& gruppa);  // проверка формата группы
};

#endif
