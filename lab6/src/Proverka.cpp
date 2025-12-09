#include "Proverka.h"

using namespace std;

bool Proverka::validnajaPochta(const string& pochta) {  // проверка email
    regex shablon(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");  // регулярное выражение regex это 
    return regex_match(pochta, shablon);  // проверка совпадения
}

bool Proverka::bezopasnyjVvod(const string& tekst) {  // проверка безопасности
    string opasnye = "';\"\\\\";  // опасные символы
    for (char c : opasnye) {  // цикл по символам
        if (tekst.find(c) != string::npos) {  // поиск опасного символа
            return false;  // найден опасный символ
        }
    }
    return true;  // безопасно
}

bool Proverka::validnajaDlina(const string& imja) {  // проверка длины
    return imja.length() >= 1 && imja.length() <= 100;  // диапазон 1-100 символов
}

bool Proverka::validnyjBall(int ball) {  // проверка оценки
    return ball >= 0 && ball <= 100;  // диапазон 0-100
}

bool Proverka::validnajaGruppa(const string& gruppa) {  // проверка группы
    return gruppa.length() >= 2 && gruppa.length() <= 20;  // диапазон 2-20 символов
}
