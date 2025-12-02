#ifndef ADRES_H
#define ADRES_H

#include <string>

struct Adres {
    std::string ulica;  // улица
    std::string gorod;  // город
    std::string index;  // почтовый индекс
    std::string strana;  // страна

    Adres();  // default конструктор
    Adres(const std::string &u, const std::string &g, const std::string &i, const std::string &s);  // параметрический конструктор
};

#endif
