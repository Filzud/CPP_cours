#include "BazaDannyh.h"
#include <iostream>

using namespace std;

BazaDannyh::BazaDannyh() : bd(nullptr), put("") {}  // конструктор

BazaDannyh::~BazaDannyh() { zakryt(); }  // деструктор

bool BazaDannyh::inicializovat(const string& imjaFajla) {  // инициализация
    put = imjaFajla;  // сохраняем путь
    if (sqlite3_open(put.c_str(), &bd) != SQLITE_OK) {  // открываем БД
        cerr << "Ошибка открытия БД: " << sqlite3_errmsg(bd) << endl;  // вывод ошибки
        return false;  // неудача
    }
    const char* sqlStudenty = "CREATE TABLE IF NOT EXISTS studenty ("  // SQL создания таблицы студентов
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "imja TEXT NOT NULL, "
        "pochta TEXT UNIQUE, "
        "gruppa TEXT);";
    char* oshibka = nullptr;  // указатель на ошибку
    if (sqlite3_exec(bd, sqlStudenty, nullptr, nullptr, &oshibka) != SQLITE_OK) {  // выполняем SQL
        cerr << "Ошибка создания таблицы studenty: " << oshibka << endl;  // вывод ошибки
        sqlite3_free(oshibka);  // освобождаем память
        return false;  // неудача
    }
    const char* sqlOcenki = "CREATE TABLE IF NOT EXISTS ocenki ("  // SQL создания таблицы оценок
        "id INTEGER PRIMARY KEY AUTOINCREMENT, " //заполнение как в sql
        "student_id INTEGER, "
        "predmet TEXT, "
        "ball INTEGER, "
        "FOREIGN KEY(student_id) REFERENCES studenty(id) ON DELETE CASCADE);";
    if (sqlite3_exec(bd, sqlOcenki, nullptr, nullptr, &oshibka) != SQLITE_OK) {  // выполняем SQL
        cerr << "Ошибка создания таблицы ocenki: " << oshibka << endl;  // вывод ошибки
        sqlite3_free(oshibka);  // освобождаем память
        return false;  // неудача
    }
    sqlite3_exec(bd, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);  // включаем внешние ключи
    sqlite3_exec(bd, "PRAGMA synchronous = NORMAL;", nullptr, nullptr, nullptr);  // оптимизация
    sqlite3_exec(bd, "PRAGMA journal_mode = WAL;", nullptr, nullptr, nullptr);  // режим журнала
    return true;  // успех
}

void BazaDannyh::zakryt() {  // закрытие БД
    if (bd) {  // проверка указателя
        sqlite3_close(bd);  // закрываем
        bd = nullptr;  // обнуляем
    }
}

sqlite3* BazaDannyh::poluchitUkazatel() { return bd; }  // получить указатель
