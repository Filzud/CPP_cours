#pragma execution_character_set("utf-8")

#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <vector>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include "DatabaseManager.h"
#include "InputValidator.h"
#include "StudentRepository.h"

using namespace std;

static void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    locale::global(locale(".UTF-8"));
    cout.sync_with_stdio(false);
}

int main() {
    setupConsole();

    DatabaseManager db;
    if (!db.initialize("students.db")) {
        cerr << u8"Не удалось инициализировать базу данных" << endl;
        return 1;
    }

    InputValidator validator;
    StudentRepository repo(db.getHandle(), validator);

    cout << u8"База данных готова: students.db" << endl;

    bool running = true;
    while (running) {
        cout << u8"\nМеню:\n"
             << u8" 1 - Добавить студента\n"
             << u8" 2 - Список студентов\n"
             << u8" 3 - Найти студента по ID\n"
             << u8" 4 - Обновить студента\n"
             << u8" 5 - Удалить студента\n"
             << u8" 6 - Добавить студента с оценками (транзакция)\n"
             << u8" 7 - Студенты по группе\n"
             << u8" 8 - Средняя оценка по предмету\n"
             << u8" 9 - Топ студентов по среднему баллу\n"
             << u8"10 - Пакетная вставка примеров\n"
             << u8" 0 - Выход\n"
             << "> ";

        int option = -1;
        if (!(cin >> option)) {
            cerr << u8"Некорректный ввод пункта меню" << endl;
            return 1;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option) {
        case 1: {
            string name, email, group;
            cout << u8"Имя: ";
            getline(cin, name);
            cout << u8"Email: ";
            getline(cin, email);
            cout << u8"Группа: ";
            getline(cin, group);
            bool ok = repo.addStudent(name, email, group);
            cout << (ok ? u8"Студент добавлен" : u8"Не удалось добавить студента") << endl;
            break;
        }
        case 2: {
            auto list = repo.getAllStudents();
            for (const auto& s : list) {
                cout << s.id << u8": " << s.name << " | " << s.email << " | " << s.groupName << endl;
            }
            if (list.empty()) cout << u8"Студенты отсутствуют" << endl;
            break;
        }
        case 3: {
            int id;
            cout << "ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            auto s = repo.getStudent(id);
            if (s) {
                cout << s->id << u8": " << s->name << " | " << s->email << " | " << s->groupName << endl;
            } else {
                cout << u8"Студент не найден" << endl;
            }
            break;
        }
        case 4: {
            int id;
            string name, email, group;
            cout << "ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << u8"Новое имя: ";
            getline(cin, name);
            cout << u8"Новый email: ";
            getline(cin, email);
            cout << u8"Новая группа: ";
            getline(cin, group);
            bool ok = repo.updateStudent(id, name, email, group);
            cout << (ok ? u8"Данные обновлены" : u8"Не удалось обновить данные") << endl;
            break;
        }
        case 5: {
            int id;
            cout << "ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool ok = repo.deleteStudent(id);
            cout << (ok ? u8"Удалено" : u8"Не удалось удалить") << endl;
            break;
        }
        case 6: {
            string name, email, group;
            cout << u8"Имя: ";
            getline(cin, name);
            cout << u8"Email: ";
            getline(cin, email);
            cout << u8"Группа: ";
            getline(cin, group);
            int n;
            cout << u8"Количество оценок: ";
            cin >> n;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            vector<Grade> grades;
            for (int i = 0; i < n; ++i) {
                Grade g;
                cout << u8"Предмет #" << (i + 1) << ": ";
                getline(cin, g.subject);
                cout << u8"Оценка (0-100): ";
                cin >> g.grade;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                grades.push_back(g);
            }
            bool ok = repo.addStudentWithGrades(name, email, group, grades);
            cout << (ok ? u8"Студент и оценки добавлены (транзакция)" : u8"Не удалось добавить с оценками") << endl;
            break;
        }
        case 7: {
            string group;
            cout << u8"Группа: ";
            getline(cin, group);
            auto list = repo.getStudentsByGroup(group);
            for (const auto& s : list) {
                cout << s.id << u8": " << s.name << " | " << s.email << " | " << s.groupName << endl;
            }
            if (list.empty()) cout << u8"Студентов в группе нет" << endl;
            break;
        }
        case 8: {
            string subject;
            cout << u8"Предмет: ";
            getline(cin, subject);
            auto avg = repo.getAverageGradeBySubject(subject);
            if (avg) {
                cout << u8"Средняя оценка по " << subject << ": " << *avg << endl;
            } else {
                cout << u8"Нет оценок по предмету" << endl;
            }
            break;
        }
        case 9: {
            int limit;
            cout << u8"Количество лучших студентов: ";
            cin >> limit;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            auto top = repo.getTopStudents(limit);
            for (const auto& p : top) {
                cout << p.first.id << u8": " << p.first.name << " среднее=" << p.second << " группа=" << p.first.groupName << endl;
            }
            if (top.empty()) cout << u8"Нет данных" << endl;
            break;
        }
        case 10: {
            vector<Student> sample = {
                {0, u8"Алиса", "alice@example.com", "CS-101"},
                {0, u8"Боб", "bob@example.com", "CS-101"},
                {0, u8"Каролина", "carol@example.com", "CS-102"},
            };
            bool ok = repo.batchInsertStudents(sample);
            cout << (ok ? u8"Пакет вставлен" : u8"Не удалось выполнить пакетную вставку") << endl;
            break;
        }
        case 0:
            running = false;
            break;
        default:
            cout << u8"Неизвестный пункт меню" << endl;
            break;
        }
    }

    return 0;
}
