#include <iostream>
#include <string>
#include <cstdlib> //внешние проги систем
#include <limits>
#ifdef _WIN32 //компилир под винду 
#ifndef NOMINMAX
#define NOMINMAX //что =б в винде не определялись макросы мин макс путаница
#endif
#include <windows.h> //кодировка консоли
#endif

using namespace std;

void setupConsole() { //настройка консоли
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); //руск язык в кут
    SetConsoleCP(CP_UTF8); //син
#endif
}

// Запускает скомпилированный бинарник taskN
void runTask(const string& name) { //поясняет назначение функции — запуск внешнего исполняемого файла по имени задачи
#ifdef _WIN32
    string cmd = name + ".exe"; //для винды расширение ексе
    int res = system(cmd.c_str()); //делаем С строку рес 0 успех иначе ошибка
#else
    string cmd = "./" + name; //для мака
    int res = system(cmd.c_str());
#endif
    if (res != 0) {
        cout << "Не удалось запустить: " << cmd << endl;
    }
}

int main() {
    setupConsole();

    while (true) {
        cout << "=============================\n";
        cout << " Лабораторная №5 (лаунчер)\n";
        cout << "=============================\n";
        cout << "1 — Задание 1 (сумма вектора)\n";
        cout << "2 — Задание 2 (producer-consumer)\n";
        cout << "3 — Задание 3 (обработка изображения)\n";
        cout << "4 — Задание 4 (π через std::async)\n";
        cout << "5 — Задание 5 (пул потоков, факториалы)\n";
        cout << "0 — Выход\n";
        cout << "Ваш выбор: ";

        int choice; //выбор сохраним
        if (!(cin >> choice)) {
            cout << "Ошибка ввода, выхожу.\n";
            break;
        }

        if (choice == 0) {
            cout << "До встречи.\n";
            break;
        }

        switch (choice) {
            case 1:
                runTask("task1");
                break;
            case 2:
                runTask("task2");
                break;
            case 3:
                runTask("task3");
                break;
            case 4:
                runTask("task4");
                break;
            case 5:
                runTask("task5");
                break;
            default:
                cout << "Неизвестный пункт меню.\n";
                break;
        }

        cout << "\nНажмите Enter, чтобы продолжить...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // пропуск всех символов
        cin.get(); // читаем один символ тут энтер 
    }

    return 0;
}
//.\launcher.exe
