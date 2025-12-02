#ifndef KLIENT_H
#define KLIENT_H

#include <string>
#include "Adres.h"
#include "Data.h"

class Klient {
protected:
    int nomer;  // номер клиента
    std::string imya;  // имя
    std::string familia;  // фамилия
    Adres adres;  // адрес клиента
    Data dataReg;  // дата регистрации
    static int counter;  // счётчик

public:
    Klient();  // default конструктор
    Klient(const std::string &im, const std::string &fam, const Adres &adr, const Data &dt);  // параметрический конструктор
    virtual ~Klient();  // деструктор

    int getNomer() const;  // получить номер
    std::string getImya() const;  // получить имя
    std::string getFamilia() const;  // получить фамилию
    Adres getAdres() const;  // получить адрес
    Data getDataReg() const;  // получить дату регистрации

    void setImya(const std::string &im);  // установить имя
    void setFamilia(const std::string &fam);  // установить фамилию
    void setAdres(const Adres &adr);  // установить адрес

    static int getCounter();  // получить счётчик

    virtual void pokazat() const;  // показать инфо
};

#endif
