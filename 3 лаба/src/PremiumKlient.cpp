#include "PremiumKlient.h"
#include <iostream>

PremiumKlient::PremiumKlient() : Klient(), uroven(1), skidka(0.0) {}  // default конструктор

PremiumKlient::PremiumKlient(const std::string &im, const std::string &fam, const Adres &adr, const Data &dt, int ur, double sk)
    : Klient(im, fam, adr, dt), uroven(ur), skidka(sk) {}  // параметрический конструктор

void PremiumKlient::setUroven(int ur) { this->uroven = ur; }  // установить уровень
void PremiumKlient::setSkidka(double sk) { this->skidka = sk; }  // установить скидку
int PremiumKlient::getUroven() const { return uroven; }  // получить уровень
double PremiumKlient::getSkidka() const { return skidka; }  // получить скидку

void PremiumKlient::pokazat() const {  // показать инфо
    Klient::pokazat();  // базовая инфо
    std::cout << "Premium уровень: " << uroven << "\n";  // уровень
    std::cout << "Скидка: " << skidka * 100 << "%\n";  // скидка в процентах
}
