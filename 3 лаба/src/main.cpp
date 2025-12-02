#include <iostream>
#include <string>
#include <limits>
#include "BankSistema.h"
#include "Klient.h"
#include "PremiumKlient.h"
#include "BankSchet.h"
#include "Operaciya.h"
#include "Adres.h"
#include "Data.h"

// Чтение целого числа
int readInt(const std::string &prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {  // проверка ввода
        std::cin.clear();  // очистка флага ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // пропуск неверного ввода
        std::cout << "Ошибка! Введите число: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // очистка буфера
    return value;
}

// Чтение вещественного числа
double readDouble(const std::string &prompt) {
    double value;
    std::cout << prompt;
    while (!(std::cin >> value)) {  // проверка ввода
        std::cin.clear();  // очистка флага ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // пропуск неверного ввода
        std::cout << "Ошибка! Введите число: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // очистка буфера
    return value;
}

// Чтение даты
Data readData(const std::string &prompt) {
    std::cout << prompt;
    int den = readInt("  День: ");
    int mesyac = readInt("  Месяц: ");
    int god = readInt("  Год: ");
    return Data(den, mesyac, god);  // возврат даты
}

// Заполнение демо-данных при старте
void zagruzitDemoDannye(BankSistema &bank) {
    static bool uzheZagruzheno = false;
    if (uzheZagruzheno) {
        return;
    }
    uzheZagruzheno = true;

    Adres adr1("Ленина 1", "Москва", "101000", "Россия");
    Adres adr2("Невский 10", "Санкт-Петербург", "190000", "Россия");
    Adres adr3("Советская 5", "Екатеринбург", "620000", "Россия");

    auto kl1 = std::make_unique<Klient>("Иван", "Иванов", adr1, Data(10, 1, 2020));
    auto kl2 = std::make_unique<Klient>("Олег", "Смирнов", adr2, Data(15, 2, 2021));
    auto kl3 = std::make_unique<PremiumKlient>("Филипп", "Филиппов", adr3, Data(5, 3, 2022), 2, 10.0);

    bank.dobavitKlienta(std::move(kl1));
    bank.dobavitKlienta(std::move(kl2));
    bank.dobavitKlienta(std::move(kl3));

    BankSchet* schet1 = bank.otkrytSchet(1, TipScheta::Tekushiy, 50000, Data(15, 1, 2020));
    BankSchet* schet2 = bank.otkrytSchet(2, TipScheta::Sberegatelny, 120000, Data(20, 2, 2021));
    BankSchet* schet3 = bank.otkrytSchet(3, TipScheta::Tekushiy, 200000, Data(25, 3, 2022));

    if (schet1) {
        bank.popolnit(schet1->getNomerScheta(), 15000);
        bank.snyat(schet1->getNomerScheta(), 10000);
    }
    if (schet2) {
        bank.popolnit(schet2->getNomerScheta(), 10000);
    }
    if (schet3 && schet1) {
        bank.popolnit(schet3->getNomerScheta(), 50000);
        bank.perevesti(schet3->getNomerScheta(), schet1->getNomerScheta(), 20000);
    }
}

void zapustitMenuSotrudnika(BankSistema &bank) {
    while (true) {
        std::cout << "\n╔═══════════════════════════════════════════╗\n";
        std::cout << "║    БАНКОВСКАЯ СИСТЕМА - СОТРУДНИК         ║\n";
        std::cout << "╚═══════════════════════════════════════════╝\n";
        std::cout << "1.  Добавить обычного клиента\n";
        std::cout << "2.  Добавить премиум клиента\n";
        std::cout << "3.  Удалить клиента\n";
        std::cout << "4.  Показать всех клиентов\n";
        std::cout << "5.  Редактировать клиента\n";
        std::cout << "6.  Открыть счёт\n";
        std::cout << "7.  Закрыть счёт\n";
        std::cout << "8.  Показать все счета\n";
        std::cout << "9.  Показать счета клиента\n";
        std::cout << "10. Пополнить счёт\n";
        std::cout << "11. Снять со счёта\n";
        std::cout << "12. Перевести деньги\n";
        std::cout << "13. Показать операции\n";
        std::cout << "14. Показать информацию о банке\n";
        std::cout << "0.  Назад к выбору роли\n";
        std::cout << "───────────────────────────────────────────\n";

        int vybor = readInt("Выберите пункт: ");

        switch (vybor) {
            case 1: {  // Добавить обычного клиента
                std::cout << "\n--- Добавление обычного клиента ---\n";
                std::string imya, familia, ulica, gorod, index, strana;

                std::cout << "Имя: ";
                std::getline(std::cin, imya);
                std::cout << "Фамилия: ";
                std::getline(std::cin, familia);
                std::cout << "Улица: ";
                std::getline(std::cin, ulica);
                std::cout << "Город: ";
                std::getline(std::cin, gorod);
                std::cout << "Индекс: ";
                std::getline(std::cin, index);
                std::cout << "Страна: ";
                std::getline(std::cin, strana);

                Data data = readData("Дата регистрации:\n");

                Adres adres(ulica, gorod, index, strana);
                auto klient = std::make_unique<Klient>(imya, familia, adres, data);
                bank.dobavitKlienta(std::move(klient));  // добавляем
                std::cout << "Клиент добавлен!\n";
                break;
            }

            case 2: {  // Добавить премиум клиента
                std::cout << "\n--- Добавление премиум клиента ---\n";
                std::string imya, familia, ulica, gorod, index, strana;

                std::cout << "Имя: ";
                std::getline(std::cin, imya);
                std::cout << "Фамилия: ";
                std::getline(std::cin, familia);
                std::cout << "Улица: ";
                std::getline(std::cin, ulica);
                std::cout << "Город: ";
                std::getline(std::cin, gorod);
                std::cout << "Индекс: ";
                std::getline(std::cin, index);
                std::cout << "Страна: ";
                std::getline(std::cin, strana);

                Data data = readData("Дата регистрации:\n");
                int uroven = readInt("Уровень премиум: ");
                double skidka = readDouble("Скидка (%): ");

                Adres adres(ulica, gorod, index, strana);
                auto klient = std::make_unique<PremiumKlient>(imya, familia, adres, data, uroven, skidka);
                bank.dobavitKlienta(std::move(klient));  // добавляем
                std::cout << "Премиум клиент добавлен!\n";
                break;
            }

            case 3: {  // Удалить клиента
                int nomer = readInt("Введите номер клиента: ");
                if (bank.udalitKlienta(nomer)) {  // удаляем
                    std::cout << "Клиент удалён!\n";
                } else {
                    std::cout << "Клиент не найден!\n";
                }
                break;
            }

            case 4: {  // Показать всех клиентов
                bank.pokazatKlientov();  // показываем
                break;
            }

            case 5: {  // Редактировать клиента
                std::cout << "\n--- Редактирование клиента ---\n";
                int nomer = readInt("Номер клиента: ");

                Klient* klient = bank.poluchitKlienta(nomer);
                if (!klient) {
                    std::cout << "Клиент не найден!\n";
                    break;
                }

                std::string imya, familia, ulica, gorod, index, strana;
                std::cout << "Новое имя: ";
                std::getline(std::cin, imya);
                std::cout << "Новая фамилия: ";
                std::getline(std::cin, familia);
                std::cout << "Новая улица: ";
                std::getline(std::cin, ulica);
                std::cout << "Новый город: ";
                std::getline(std::cin, gorod);
                std::cout << "Новый индекс: ";
                std::getline(std::cin, index);
                std::cout << "Новая страна: ";
                std::getline(std::cin, strana);

                Adres adres(ulica, gorod, index, strana);
                bank.redaktirovatKlienta(nomer, imya, familia, adres);  // редактируем
                break;
            }

            case 6: {  // Открыть счёт
                std::cout << "\n--- Открытие счёта ---\n";
                int idKlienta = readInt("ID клиента: ");

                std::cout << "Тип счёта (0 - Текущий, 1 - Сберегательный): ";
                int tipInt = readInt("");
                TipScheta tip = (tipInt == 0) ? TipScheta::Tekushiy : TipScheta::Sberegatelny;

                double balans = readDouble("Начальный баланс: ");
                Data data = readData("Дата открытия:\n");

                bank.otkrytSchet(idKlienta, tip, balans, data);  // открываем
                break;
            }

            case 7: {  // Закрыть счёт
                int nomerScheta = readInt("Номер счёта: ");
                bank.zakrytSchet(nomerScheta);  // закрываем
                break;
            }

            case 8: {  // Показать все счета
                bank.pokazatScheta();  // показываем
                break;
            }

            case 9: {  // Показать счета клиента
                int idKlienta = readInt("ID клиента: ");
                auto scheta = bank.poluchitSchetaKlienta(idKlienta);  // получаем

                if (scheta.empty()) {
                    std::cout << "У клиента нет активных счетов.\n";
                } else {
                    std::cout << "\n--- Счета клиента " << idKlienta << " ---\n";
                    for (auto schet : scheta) {
                        schet->pokazatInfo();  // показываем
                        std::cout << "------------------------------------\n";
                    }
                }
                break;
            }

            case 10: {  // Пополнить счёт
                int nomerScheta = readInt("Номер счёта: ");
                double summa = readDouble("Сумма пополнения: ");
                bank.popolnit(nomerScheta, summa);  // пополняем
                break;
            }

            case 11: {  // Снять со счёта
                int nomerScheta = readInt("Номер счёта: ");
                double summa = readDouble("Сумма снятия: ");
                bank.snyat(nomerScheta, summa);  // снимаем
                break;
            }

            case 12: {  // Перевести деньги
                int schetOt = readInt("Счёт отправителя: ");
                int schetK = readInt("Счёт получателя: ");
                double summa = readDouble("Сумма перевода: ");
                bank.perevesti(schetOt, schetK, summa);  // переводим
                break;
            }

            case 13: {  // Показать операции
                bank.pokazatOperacii();  // показываем
                break;
            }

            case 14: {  // Показать информацию о банке
                bank.pokazatInfoBanka();  // показываем
                break;
            }

            case 0: {  // Назад
                std::cout << "Возврат к выбору роли.\n";
                return;
            }

            default: {  // Неверный ввод
                std::cout << "Неверный выбор! Попробуйте снова.\n";
                break;
            }
        }
    }
}

void zapustitKabinetKlienta(BankSistema &bank, int idKlienta) {
    while (true) {
        std::cout << "\n╔═══════════════════════════════════════════╗\n";
        std::cout << "║         ЛИЧНЫЙ КАБИНЕТ КЛИЕНТА            ║\n";
        std::cout << "╚═══════════════════════════════════════════╝\n";
        std::cout << "1. Показать мои данные\n";
        std::cout << "2. Показать мои счета\n";
        std::cout << "3. Пополнить мой счёт\n";
        std::cout << "4. Снять с моего счёта\n";
        std::cout << "5. Перевести с моего счёта\n";
        std::cout << "6. Показать мои операции\n";
        std::cout << "0. Выход в выбор роли\n";
        std::cout << "───────────────────────────────────────────\n";

        int vybor = readInt("Выберите пункт: ");

        switch (vybor) {
            case 1: {
                Klient* klient = bank.poluchitKlienta(idKlienta);
                if (klient) {
                    klient->pokazat();
                } else {
                    std::cout << "Клиент не найден.\n";
                    return;
                }
                break;
            }
            case 2: {
                auto scheta = bank.poluchitSchetaKlienta(idKlienta);
                if (scheta.empty()) {
                    std::cout << "У вас нет активных счетов.\n";
                } else {
                    std::cout << "\n--- Ваши счета ---\n";
                    for (auto schet : scheta) {
                        schet->pokazatInfo();
                        std::cout << "------------------------------------\n";
                    }
                }
                break;
            }
            case 3: {
                int nomerScheta = readInt("Номер вашего счёта: ");
                if (!bank.schetPrinadlezhitKlientu(idKlienta, nomerScheta)) {
                    std::cout << "Можно работать только со своими счетами.\n";
                    break;
                }
                double summa = readDouble("Сумма пополнения: ");
                bank.popolnit(nomerScheta, summa);
                break;
            }
            case 4: {
                int nomerScheta = readInt("Номер вашего счёта: ");
                if (!bank.schetPrinadlezhitKlientu(idKlienta, nomerScheta)) {
                    std::cout << "Можно работать только со своими счетами.\n";
                    break;
                }
                double summa = readDouble("Сумма снятия: ");
                bank.snyat(nomerScheta, summa);
                break;
            }
            case 5: {
                int schetOt = readInt("Счёт отправителя (ваш): ");
                if (!bank.schetPrinadlezhitKlientu(idKlienta, schetOt)) {
                    std::cout << "Можно работать только со своими счетами.\n";
                    break;
                }
                int schetK = readInt("Счёт получателя: ");
                double summa = readDouble("Сумма перевода: ");
                bank.perevesti(schetOt, schetK, summa);
                break;
            }
            case 6: {
                bank.pokazatOperaciiKlienta(idKlienta);
                break;
            }
            case 0: {
                std::cout << "Выход из личного кабинета.\n";
                return;
            }
            default: {
                std::cout << "Неверный выбор! Попробуйте снова.\n";
                break;
            }
        }
    }
}

// Главная функция
int main() {
    BankSistema bank;  // создаём систему банка
    zagruzitDemoDannye(bank);

    while (true) {
        std::cout << "\n╔═══════════════════════════════════════════╗\n";
        std::cout << "║        БАНКОВСКАЯ СИСТЕМА - РОЛИ          ║\n";
        std::cout << "╚═══════════════════════════════════════════╝\n";
        std::cout << "1. Войти как сотрудник банка\n";
        std::cout << "2. Войти как клиент\n";
        std::cout << "0. Выход\n";
        std::cout << "───────────────────────────────────────────\n";

        int rol = readInt("Выберите роль: ");
        if (rol == 1) {
            zapustitMenuSotrudnika(bank);
        } else if (rol == 2) {
            int idKlienta = readInt("Введите ваш ID клиента: ");
            Klient* klient = bank.poluchitKlienta(idKlienta);
            if (!klient) {
                std::cout << "Клиент не найден. Обратитесь в банк.\n";
            } else {
                zapustitKabinetKlienta(bank, idKlienta);
            }
        } else if (rol == 0) {
            std::cout << "До свидания!\n";
            break;
        } else {
            std::cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }

    return 0;
}
