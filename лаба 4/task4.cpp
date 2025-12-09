#include <iostream>
#include <future> //асинхронность высокого уровня
#include <random>
#include <vector>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using namespace std;

void setupConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

class PiCalculator {
public:
    // Монте-Карло для вычисления π
    double calculatePiPortion(int total_points) { //скок точек мы сгенерируем значение п по точкам
        mt19937 gen(random_device{}()); //разная последовательность 
        uniform_real_distribution<double> dist(0.0, 1.0); //равномерное распределение

        int inside = 0;
        for (int i = 0; i < total_points; ++i) {
            double x = dist(gen);
            double y = dist(gen); //генер случ точки в квадрате 0 1
            if (x * x + y * y <= 1.0) {
                ++inside;
            }
        }

        return 4.0 * inside / static_cast<double>(total_points);
    }

    // Параллельный расчет π
    double calculatePiParallel(int total_points, int num_tasks) { // сколько задач/потоков
        if (num_tasks <= 0) num_tasks = 1;

        vector<future<double>> futures;
        int points_per_task = total_points / num_tasks; //скок точ на кажду задачу

        for (int i = 0; i < num_tasks; ++i) {
            futures.push_back(
                async(launch::async, &PiCalculator::calculatePiPortion,
                      this, points_per_task) //запуск функции асинхронно сразу новый поток 
            );
        }

        double sum = 0.0; //накапливать сумму приближений π от всех задач
        try { //если гет бросит исключение
            for (auto& f : futures) {
                sum += f.get(); //ожидает завершения задачи 
            }
        } catch (const exception& e) { //если поймали исключение или его наследника выводим
            cerr << "Ошибка при расчёте π: " << e.what() << endl; //серр ошибка поток 
            return 0.0;
        } catch (...) { //любые другие исключения
            cerr << "Неизвестная ошибка при расчёте π\n";
            return 0.0;
        }

        return sum / num_tasks; //усрредне резы
    }
};

int main() {
    setupConsole();

    PiCalculator calc; //создаём объект калькулятора π

    double pi = calc.calculatePiParallel(1'000'000, 4); //параллельный расчёт π лям точ и 4 таски

    cout.setf(ios::fixed);
    cout.precision(6);
    cout << "Приближённое π: " << pi << endl;

    return 0;
}
