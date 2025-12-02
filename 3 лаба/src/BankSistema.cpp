#include "BankSistema.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>

// Добавить клиента в систему
void BankSistema::dobavitKlienta(std::unique_ptr<Klient> klient) {
    klienty.push_back(std::move(klient));  // добавляем в вектор
}

// Удалить клиента по номеру
bool BankSistema::udalitKlienta(int nomer) {
    auto it = std::find_if(klienty.begin(), klienty.end(),
        [nomer](const std::unique_ptr<Klient> &k) { return k->getNomer() == nomer; });

    if (it != klienty.end()) {  // если найден
        // Закрываем все счета клиента
        std::vector<BankSchet*> schetaKlienta = poluchitSchetaKlienta(nomer);
        for (auto schet : schetaKlienta) {
            schet->zakryt();  // закрываем счёт
        }
        klienty.erase(it);  // удаляем клиента
        return true;
    }
    return false;  // клиент не найден
}

// Получить клиента по номеру
Klient* BankSistema::poluchitKlienta(int nomer) {
    return naytiKlienta(nomer);  // используем приватный метод
}

// Найти клиента по номеру (приватный)
Klient* BankSistema::naytiKlienta(int nomer) {
    for (auto &klient : klienty) {
        if (klient->getNomer() == nomer) {
            return klient.get();  // возвращаем указатель
        }
    }
    return nullptr;  // не найден
}

// Показать всех клиентов
void BankSistema::pokazatKlientov() const {
    if (klienty.empty()) {
        std::cout << "Клиентов нет в системе.\n";
        return;
    }

    std::cout << "\n========== СПИСОК КЛИЕНТОВ ==========\n";
    for (const auto &klient : klienty) {
        klient->pokazat();  // виртуальный метод
        std::cout << "------------------------------------\n";
    }
}

// Редактировать данные клиента
void BankSistema::redaktirovatKlienta(int nomer, const std::string &imya,
                                       const std::string &familia, const Adres &adres) {
    Klient* klient = naytiKlienta(nomer);
    if (klient) {
        klient->setImya(imya);  // новое имя
        klient->setFamilia(familia);  // новая фамилия
        klient->setAdres(adres);  // новый адрес
        std::cout << "Клиент обновлён!\n";
    } else {
        std::cout << "Клиент не найден!\n";
    }
}

bool BankSistema::schetPrinadlezhitKlientu(int idKlienta, int nomerScheta) const {
    for (const auto &schet : scheta) {
        if (schet.getNomerScheta() == nomerScheta && schet.getIdKlienta() == idKlienta && schet.isAktiven()) {
            return true;
        }
    }
    return false;
}

// Открыть новый счёт
BankSchet* BankSistema::otkrytSchet(int idKlienta, TipScheta tip,
                                     double nachBalans, const Data &data) {
    Klient* klient = naytiKlienta(idKlienta);
    if (!klient) {
        std::cout << "Клиент не найден!\n";
        return nullptr;
    }

    scheta.emplace_back(idKlienta, tip, nachBalans, data);  // создаём счёт
    std::cout << "Счёт открыт! Номер: " << scheta.back().getNomerScheta() << "\n";
    return &scheta.back();  // возвращаем указатель
}

// Закрыть счёт
bool BankSistema::zakrytSchet(int nomerScheta) {
    BankSchet* schet = naytiSchet(nomerScheta);
    if (schet) {
        schet->zakryt();  // закрываем
        std::cout << "Счёт закрыт!\n";
        return true;
    }
    std::cout << "Счёт не найден!\n";
    return false;
}

// Найти счёт по номеру (приватный)
BankSchet* BankSistema::naytiSchet(int nomerScheta) {
    for (auto &schet : scheta) {
        if (schet.getNomerScheta() == nomerScheta) {
            return &schet;  // возвращаем указатель
        }
    }
    return nullptr;  // не найден
}

// Получить все счета клиента
std::vector<BankSchet*> BankSistema::poluchitSchetaKlienta(int idKlienta) {
    std::vector<BankSchet*> result;
    for (auto &schet : scheta) {
        if (schet.getIdKlienta() == idKlienta && schet.isAktiven()) {
            result.push_back(&schet);  // добавляем активные счета
        }
    }
    return result;
}

// Показать все счета
void BankSistema::pokazatScheta() const {
    if (scheta.empty()) {
        std::cout << "Счетов нет в системе.\n";
        return;
    }

    std::cout << "\n========== СПИСОК СЧЕТОВ ==========\n";
    for (const auto &schet : scheta) {
        schet.pokazatInfo();  // показываем инфо
        std::cout << "------------------------------------\n";
    }
}

// Пополнить счёт
void BankSistema::popolnit(int nomerScheta, double summa) {
    BankSchet* schet = naytiSchet(nomerScheta);
    if (schet && schet->isAktiven()) {
        schet->popolnit(summa);  // пополняем
        operacii.emplace_back(-1, nomerScheta, summa, TipOperacii::Popolnenie);  // записываем операцию
        std::cout << "Счёт пополнен на " << summa << "\n";
    } else {
        std::cout << "Счёт не найден или неактивен!\n";
    }
}

// Снять со счёта
void BankSistema::snyat(int nomerScheta, double summa) {
    BankSchet* schet = naytiSchet(nomerScheta);
    if (schet && schet->isAktiven()) {
        if (schet->snyat(summa)) {  // пытаемся снять
            operacii.emplace_back(nomerScheta, -1, summa, TipOperacii::Snyatie);  // записываем операцию
            std::cout << "Снято " << summa << " со счёта\n";
        } else {
            std::cout << "Недостаточно средств!\n";
        }
    } else {
        std::cout << "Счёт не найден или неактивен!\n";
    }
}

// Перевести деньги
void BankSistema::perevesti(int schetOt, int schetK, double summa) {
    BankSchet* ot = naytiSchet(schetOt);
    BankSchet* k = naytiSchet(schetK);

    if (!ot || !ot->isAktiven()) {
        std::cout << "Счёт отправителя не найден или неактивен!\n";
        return;
    }
    if (!k || !k->isAktiven()) {
        std::cout << "Счёт получателя не найден или неактивен!\n";
        return;
    }

    if (ot->perevesti(*k, summa)) {  // делаем перевод
        operacii.emplace_back(schetOt, schetK, summa, TipOperacii::Perevod);  // записываем операцию
        std::cout << "Перевод выполнен: " << summa << "\n";
    } else {
        std::cout << "Недостаточно средств для перевода!\n";
    }
}

// Показать все операции
void BankSistema::pokazatOperacii() const {
    if (operacii.empty()) {
        std::cout << "Операций не было.\n";
        return;
    }

    std::cout << "\n========== СПИСОК ОПЕРАЦИЙ ==========\n";
    for (const auto &op : operacii) {
        op.pokazatInfo();  // показываем инфо
        std::cout << "------------------------------------\n";
    }
}

void BankSistema::pokazatOperaciiKlienta(int idKlienta) const {
    std::unordered_set<int> schetaKlienta;
    for (const auto &schet : scheta) {
        if (schet.getIdKlienta() == idKlienta) {
            schetaKlienta.insert(schet.getNomerScheta());
        }
    }
    bool estOperacii = false;
    for (const auto &op : operacii) {
        if (schetaKlienta.count(op.getSchetOt()) || schetaKlienta.count(op.getSchetK())) {
            op.pokazatInfo();
            std::cout << "------------------------------------\n";
            estOperacii = true;
        }
    }
    if (!estOperacii) {
        std::cout << "Для этого клиента операций нет.\n";
    }
}

// Показать общую информацию банка
void BankSistema::pokazatInfoBanka() const {
    std::cout << "\n========== ИНФОРМАЦИЯ О БАНКЕ ==========\n";
    std::cout << "Всего клиентов: " << klienty.size() << "\n";

    int aktivnyeScheta = 0;
    double obshiyBalans = 0.0;
    for (const auto &schet : scheta) {
        if (schet.isAktiven()) {
            aktivnyeScheta++;  // считаем активные
            obshiyBalans += schet.getBalans();  // суммируем баланс
        }
    }

    std::cout << "Активных счетов: " << aktivnyeScheta << "\n";
    std::cout << "Общий баланс: " << obshiyBalans << "\n";
    std::cout << "Всего операций: " << operacii.size() << "\n";
    std::cout << "========================================\n";
}
