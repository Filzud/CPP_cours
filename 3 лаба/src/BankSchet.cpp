#include "BankSchet.h"
#include <iostream>

int BankSchet::counterSchetov = 0;  // инициализация счётчика

BankSchet::BankSchet(int idKl, TipScheta t, double nachBalans, const Data &dt)
    : nomerScheta(++counterSchetov), idKlienta(idKl), balans(nachBalans), tip(t), dataOtkrytiya(dt), aktiven(true) {}  // конструктор

int BankSchet::getNomerScheta() const { return nomerScheta; }  // получить номер
int BankSchet::getIdKlienta() const { return idKlienta; }  // получить ID клиента
double BankSchet::getBalans() const { return balans; }  // получить баланс
TipScheta BankSchet::getTip() const { return tip; }  // получить тип
Data BankSchet::getDataOtkrytiya() const { return dataOtkrytiya; }  // получить дату открытия
bool BankSchet::isAktiven() const { return aktiven; }  // активен ли

void BankSchet::popolnit(double summa) {  // пополнить счёт
    if (summa > 0) {  // проверка суммы
        balans += summa;  // добавляем к балансу
    }
}

bool BankSchet::snyat(double summa) {  // снять со счёта
    if (summa > 0 && balans >= summa) {  // проверка суммы и баланса
        balans -= summa;  // вычитаем из баланса
        return true;  // успех
    }
    return false;  // недостаточно средств
}

bool BankSchet::perevesti(BankSchet &poluchatel, double summa) {  // перевести на другой счёт
    if (this->snyat(summa)) {  // пытаемся снять
        poluchatel.popolnit(summa);  // пополняем счёт получателя
        return true;  // успех
    }
    return false;  // не удалось
}

void BankSchet::zakryt() { aktiven = false; }  // закрыть счёт
void BankSchet::otkryt() { aktiven = true; }  // открыть счёт

int BankSchet::getCounterSchetov() { return counterSchetov; }  // получить счётчик

void BankSchet::pokazatInfo() const {  // показать инфо
    std::cout << "Номер счёта: " << nomerScheta << "\n";  // номер
    std::cout << "ID клиента: " << idKlienta << "\n";  // ID клиента
    std::cout << "Баланс: " << balans << "\n";  // баланс
    std::cout << "Тип: " << (tip == TipScheta::Tekushiy ? "Текущий" : "Сберегательный") << "\n";  // тип
    std::cout << "Дата открытия: " << dataOtkrytiya.toStr() << "\n";  // дата
    std::cout << "Статус: " << (aktiven ? "Активен" : "Закрыт") << "\n";  // статус
}
