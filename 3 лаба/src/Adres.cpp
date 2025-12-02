#include "Adres.h"

Adres::Adres() : ulica(""), gorod(""), index(""), strana("") {}  // default конструктор

Adres::Adres(const std::string &u, const std::string &g, const std::string &i, const std::string &s)
    : ulica(u), gorod(g), index(i), strana(s) {}  // параметрический конструктор
