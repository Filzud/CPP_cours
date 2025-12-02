#include "Data.h"
#include <sstream>
#include <iomanip>

Data::Data() : den(1), mesyac(1), god(2000) {}  // default конструктор

Data::Data(int d, int m, int g) : den(d), mesyac(m), god(g) {}  // параметрический конструктор

std::string Data::toStr() const {  // преобразование в строку
    std::ostringstream out;  // поток
    out << std::setfill('0') << std::setw(2) << den << "."  // день
        << std::setfill('0') << std::setw(2) << mesyac << "."  // месяц
        << god;  // год
    return out.str();  // результат
}
