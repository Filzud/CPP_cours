#include "Operaciya.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int Operaciya::counterOperaciy = 0;  // инициализация счётчика

Operaciya::Operaciya(int ot, int k, double s, TipOperacii t)
    : nomer(++counterOperaciy), schetOt(ot), schetK(k), summa(s), tip(t) {  // конструктор
    auto now = std::chrono::system_clock::now();  // текущее время
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);  // конвертация
    std::ostringstream oss;  // поток
    oss << std::put_time(std::localtime(&t_now), "%Y-%m-%d %H:%M:%S");  // форматирование
    vremya = oss.str();  // сохранение
}

int Operaciya::getNomer() const { return nomer; }  // получить номер
int Operaciya::getSchetOt() const { return schetOt; }  // получить счёт отправителя
int Operaciya::getSchetK() const { return schetK; }  // получить счёт получателя
double Operaciya::getSumma() const { return summa; }  // получить сумму
std::string Operaciya::getVremya() const { return vremya; }  // получить время
TipOperacii Operaciya::getTip() const { return tip; }  // получить тип

void Operaciya::pokazatInfo() const {  // показать инфо
    std::cout << "Операция #" << nomer << "\n";  // номер
    std::string tipStr;  // строка типа
    if (tip == TipOperacii::Popolnenie) tipStr = "Пополнение";  // пополнение
    else if (tip == TipOperacii::Snyatie) tipStr = "Снятие";  // снятие
    else tipStr = "Перевод";  // перевод
    std::cout << "Тип: " << tipStr << "\n";  // тип
    std::cout << "Со счёта: " << schetOt << " -> На счёт: " << schetK << "\n";  // счета
    std::cout << "Сумма: " << summa << "\n";  // сумма
    std::cout << "Время: " << vremya << "\n";  // время
}

int Operaciya::getCounterOperaciy() { return counterOperaciy; }  // получить счётчик
