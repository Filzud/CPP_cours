#ifndef PREMIUMKLIENT_H
#define PREMIUMKLIENT_H

#include "Klient.h"

class PremiumKlient : public Klient {
private:
    int uroven;  // уровень премиум
    double skidka;  // скидка

public:
    PremiumKlient();  // default конструктор
    PremiumKlient(const std::string &im, const std::string &fam, const Adres &adr, const Data &dt, int ur, double sk);  // параметрический конструктор

    void setUroven(int ur);  // установить уровень
    void setSkidka(double sk);  // установить скидку
    int getUroven() const;  // получить уровень
    double getSkidka() const;  // получить скидку
    void pokazat() const override;  // показать инфо
};

#endif
