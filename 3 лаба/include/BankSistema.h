#ifndef BANKSISTEMA_H
#define BANKSISTEMA_H

#include <vector>
#include <memory>
#include "Klient.h"
#include "PremiumKlient.h"
#include "BankSchet.h"
#include "Operaciya.h"

class BankSistema {
private:
    std::vector<std::unique_ptr<Klient>> klienty;  // список клиентов
    std::vector<BankSchet> scheta;  // список счетов
    std::vector<Operaciya> operacii;  // список операций

    Klient* naytiKlienta(int nomer);  // найти клиента
    BankSchet* naytiSchet(int nomerScheta);  // найти счёт

public:
    BankSistema() = default;  // конструктор

    void dobavitKlienta(std::unique_ptr<Klient> klient);  // добавить клиента
    bool udalitKlienta(int nomer);  // удалить клиента
    Klient* poluchitKlienta(int nomer);  // получить клиента
    void pokazatKlientov() const;  // показать клиентов
    void redaktirovatKlienta(int nomer, const std::string &imya, const std::string &familia, const Adres &adres);  // редактировать клиента
    bool schetPrinadlezhitKlientu(int idKlienta, int nomerScheta) const;  // проверка принадлежности счёта

    BankSchet* otkrytSchet(int idKlienta, TipScheta tip, double nachBalans, const Data &data);  // открыть счёт
    bool zakrytSchet(int nomerScheta);  // закрыть счёт
    std::vector<BankSchet*> poluchitSchetaKlienta(int idKlienta);  // получить счета клиента
    void pokazatScheta() const;  // показать счета

    void popolnit(int nomerScheta, double summa);  // пополнить счёт
    void snyat(int nomerScheta, double summa);  // снять со счёта
    void perevesti(int schetOt, int schetK, double summa);  // перевести

    void pokazatOperacii() const;  // показать операции
    void pokazatOperaciiKlienta(int idKlienta) const;  // показать операции клиента
    void pokazatInfoBanka() const;  // показать инфо банка
};

#endif
