#include <iostream>
#include <vector>
#include <thread> // класс для работы с потоками
#include <mutex> // синхрон потоков
#include <chrono> // время 
#include <random>
#ifdef _WIN32
#ifndef NOMINMAX //макросы мин макс защита 
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

class VectorSumCalculator { // отличие от вектора что считает сумму в однопоток и многопоток 
private:
    vector<int> data;
    mutex sum_mutex; // защита от гонки данных  

    // Считает сумму части вектора [start, end) и добавляет в общий итог.
    void partialSum(size_t start, size_t end, long long& total_sum) {
        long long local_sum = 0; //Каждый поток считает свою часть во временную переменную
        for (size_t i = start; i < end; ++i) {
            local_sum += data[i]; //идём по всем и добавляем к локалу сумме
        }

        lock_guard<mutex> lock(sum_mutex); // блок мьютекса
        total_sum += local_sum; // защита участка от достопу нескольких потоков
    }

public:
    // Заполняет вектор случайными числами от 1 до 100.
    VectorSumCalculator(size_t size) {
        data.resize(size); //меняем размер вектора на сайз
        mt19937 gen(random_device{}()); // генератор сулчайных чисел каждый запуск разные числ
        uniform_int_distribution<int> dist(1, 100); // дист даёт целое цисло в интервале 1 100

        for (size_t i = 0; i < size; ++i) {
            data[i] = dist(gen); // присвойка к ай
        }
    }

    long long calculateSingleThreaded() { //метод сумма в одном потоке
        long long sum = 0; // накопление суммы
        for (size_t i = 0; i < data.size(); ++i) {
            sum += data[i]; //  добавка каждого элемента в сумму
        }
        return sum;
    }

    long long calculateMultiThreaded(int num_threads) { // мгопоток суммиро скок используем потоков
        if (num_threads <= 0) num_threads = 1;

        long long total_sum = 0; // добавка лок сумму через мьютекс
        vector<thread> threads; // храние потоков чтоб потом добавлять 

        size_t part_size = data.size() / num_threads; // скок элементов каждому потоку вектор на части
        size_t start = 0; // нач индекс

        for (int i = 0; i < num_threads; ++i) {
            size_t end = (i == num_threads - 1) ? data.size() : start + part_size; //берём до конца вектора если размер не делится нацело
            threads.emplace_back(&VectorSumCalculator::partialSum, 
                                 this, start, end, ref(total_sum)); // поток прямо тут с 2 аргументами 
            start = end; // виз текущий параметры метода реф=ссылка на тотал сум
        }

        for (auto& t : threads) {
            t.join(); // ожидание завершения потока блокирует текущий пока т не закончился
        }

        return total_sum;
    }
};

int main() {
    setupConsole();

    VectorSumCalculator calc(10'000'000); // объект  много элементов

    auto start_single = chrono::steady_clock::now(); // вывод типа компилятором часы 
    long long single = calc.calculateSingleThreaded(); // счёт суммы в одном потоке и в сигнл пихаем
    auto end_single = chrono::steady_clock::now(); // фиксируем  время однопотока

    auto start_multi = chrono::steady_clock::now();
    long long multi = calc.calculateMultiThreaded(4); // на 4 потока
    auto end_multi = chrono::steady_clock::now();

    auto time_single = chrono::duration_cast<chrono::milliseconds>(end_single - start_single).count(); // дюратион длителность потом милисекунды потом целое число каунт
    auto time_multi  = chrono::duration_cast<chrono::milliseconds>(end_multi - start_multi).count();

    cout << "Сумма (один поток): " << single
         << ", время: " << time_single << " мс\n";
    cout << "Сумма (4 потока): " << multi
         << ", время: " << time_multi  << " мс\n";

    return 0;
}
