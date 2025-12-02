#ifndef BANKSCHET_H
#define BANKSCHET_H

#include "Data.h"

enum class TipScheta {
    Tekushiy,  // текущий счёт
    Sberegatelny  // сберегательный счёт
};

class BankSchet {
private:
    int nomerScheta;  // номер счёта
    int idKlienta;  // ID клиента
    double balans;  // баланс
    TipScheta tip;  // тип счёта
    Data dataOtkrytiya;  // дата открытия
    bool aktiven;  // активен ли счёт
    static int counterSchetov;  // счётчик счетов

public:
    BankSchet(int idKl, TipScheta t, double nachBalans, const Data &dt);  // конструктор

    int getNomerScheta() const;  // получить номер
    int getIdKlienta() const;  // получить ID клиента
    double getBalans() const;  // получить баланс
    TipScheta getTip() const;  // получить тип
    Data getDataOtkrytiya() const;  // получить дату открытия
    bool isAktiven() const;  // активен ли

    void popolnit(double summa);  // пополнить счёт
    bool snyat(double summa);  // снять со счёта
    bool perevesti(BankSchet &poluchatel, double summa);  // перевести на другой счёт
    void zakryt();  // закрыть счёт
    void otkryt();  // открыть счёт

    static int getCounterSchetov();  // получить счётчик
    void pokazatInfo() const;  // показать инфо
};

#endif
