#include <iostream>
#include <thread>
#include <vector>
#include <queue> //очередь
#include <future> 
#include <functional>// для войд хранение объектов
#include <mutex>
#include <condition_variable> //ожидание задач 
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

class ThreadPool {
private:
    vector<thread> workers;
    queue<function<void()>> tasks; //очер зад

    mutex queue_mutex; 
    condition_variable condition; //потоки спят пока пуста очередь как появл будят
    bool stop = false; //пул остановлен 

public:
    // Создаём num_threads рабочих потоков
    ThreadPool(size_t num_threads) { //конструктор 
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this]() { /// новый поток в векторе рабов . на ферпул виз
                while (true) {
                    function<void()> task; //переменная для сохранения задачи одной из очереди

                    {
                        unique_lock<mutex> lock(queue_mutex);
                        condition.wait(lock, [this]() { //лок на вейта
                            return stop || !tasks.empty(); //спит пока условие не истина
                        });

                        if (stop && tasks.empty()) {
                            return; //пул остановлен очередь пуста
                        }

                        task = std::move(tasks.front());
                        tasks.pop(); //удаляем из очереди
                    }

                    task(); // выполняем задачу
                }
            });
        }
    }

    // Добавляем задачу, которая ничего не принимает, но что-то возвращает
    template<typename F> //шаблон функц лямбда
    auto submit(F f) -> future<decltype(f())> { //принимаем ф без аргументов тип значения
        using return_type = decltype(f()); //выводим псевдоним реторн удобнее

        auto task = make_shared<packaged_task<return_type()>>(f); //обёртка над функцией при вызове таск выполнит ф и во фьючер удобнее передача
        future<return_type> res = task->get_future(); //получ фьючер выполняя таск

        {
            lock_guard<mutex> lock(queue_mutex);
            if (stop) {
                throw runtime_error("submit on stopped ThreadPool"); //исключение 
            }
            tasks.emplace([task]() { //добавляем в очередь лямбду
                (*task)(); // запуск ф резы в фьючер
            });
        }

        condition.notify_one(); //будим один раб поток новую задачу увидел
        return res; //фьючер 
    }

    // Деструктор: останавливаем пул
    ~ThreadPool() {
        {
            lock_guard<mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();

        for (auto& w : workers) {
            if (w.joinable()) { //если поток ещё не присоединён то джойн ждёт завершения
                w.join();
            }
        }
    }
};

// Вычисление факториала
unsigned long long factorial(int n) {
    unsigned long long result = 1; //нач знач произведения
    for (int i = 2; i <= n; ++i) {
        result *= static_cast<unsigned long long>(i);
    }
    return result;
}

int main() {
    setupConsole();

    ThreadPool pool(4);
    vector<future<unsigned long long>> futures;

    // Добавляем задачи в пул
    for (int n = 5; n <= 12; ++n) { //считаем факториал от 5 до 12
        futures.push_back( //сохран фьючер в вектор
            pool.submit([n]() { //кладём задачу в очередь
                return factorial(n);
            })
        );
    }

    // Получаем результаты
    for (int i = 0; i < (int)futures.size(); ++i) {
        int n = 5 + i; //начали с 5
        cout << "factorial(" << n << ") = " << futures[i].get() << endl; //гет один раз после пусто
    }

    return 0;
}
