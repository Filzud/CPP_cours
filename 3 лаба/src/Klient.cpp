#include "Klient.h"
#include <iostream>

int Klient::counter = 0;  // инициализация счётчика

Klient::Klient() : nomer(++counter), imya("No Name"), familia("No Family"), adres(), dataReg() {}  // default конструктор

Klient::Klient(const std::string &im, const std::string &fam, const Adres &adr, const Data &dt)
    : nomer(++counter), imya(im), familia(fam), adres(adr), dataReg(dt) {}  // параметрический конструктор

Klient::~Klient() {}  // деструктор

int Klient::getNomer() const { return nomer; }  // получить номер
std::string Klient::getImya() const { return imya; }  // получить имя
std::string Klient::getFamilia() const { return familia; }  // получить фамилию
Adres Klient::getAdres() const { return adres; }  // получить адрес
Data Klient::getDataReg() const { return dataReg; }  // получить дату

void Klient::setImya(const std::string &im) { this->imya = im; }  // установить имя
void Klient::setFamilia(const std::string &fam) { this->familia = fam; }  // установить фамилию
void Klient::setAdres(const Adres &adr) { this->adres = adr; }  // установить адрес

int Klient::getCounter() { return counter; }  // получить счётчик

void Klient::pokazat() const {  // показать инфо
    std::cout << "ID: " << nomer << "\n";  // номер
    std::cout << "ФИО: " << imya << " " << familia << "\n";  // имя и фамилия
    std::cout << "Адрес: " << adres.ulica << ", " << adres.gorod << ", " << adres.index << ", " << adres.strana << "\n";  // адрес
    std::cout << "Дата регистрации: " << dataReg.toStr() << "\n";  // дата
}
