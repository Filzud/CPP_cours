#ifndef DATA_H
#define DATA_H

#include <string>

struct Data {
    int den;  // день
    int mesyac;  // месяц
    int god;  // год

    Data();  // default конструктор
    Data(int d, int m, int g);  // параметрический конструктор
    std::string toStr() const;  // в строку
};

#endif
