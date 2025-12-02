#ifndef OPERACIYA_H
#define OPERACIYA_H

#include <string>
#include <chrono>
#include <ctime>

enum class TipOperacii {
    Popolnenie,  // пополнение
    Snyatie,  // снятие
    Perevod  // перевод
};

class Operaciya {
private:
    int nomer;  // номер операции
    int schetOt;  // счёт отправителя
    int schetK;  // счёт получателя
    double summa;  // сумма
    std::string vremya;  // время операции
    TipOperacii tip;  // тип операции
    static int counterOperaciy;  // счётчик операций

public:
    Operaciya(int ot, int k, double s, TipOperacii t);  // конструктор

    int getNomer() const;  // получить номер
    int getSchetOt() const;  // получить счёт отправителя
    int getSchetK() const;  // получить счёт получателя
    double getSumma() const;  // получить сумму
    std::string getVremya() const;  // получить время
    TipOperacii getTip() const;  // получить тип

    void pokazatInfo() const;  // показать инфо
    static int getCounterOperaciy();  // получить счётчик
};

#endif
