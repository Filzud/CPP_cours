#include <iostream>
#include <queue> //очередь фифо первое первым
#include <thread> //потоки
#include <mutex>
#include <condition_variable> //условные переменные  ожидание событий
#include <chrono> // время задержка
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

template<typename T> //объявл шаблона Т (люб тип инт стринг)
class ThreadSafeQueue {
private:
    queue<T> q; //очередь для элементов типа Т
    mutex mtx; // защита доступак очереди
    condition_variable cond; //потоки засыпают и просыпаются при событии (появился элемент или очередь закрыта)
    bool stopped = false;  // очередь работает можно добавлять забирать 

public:
    
    void push(T value) { //безопасное добавление в потоки (берёт по значению копию)
        {
            lock_guard<mutex> lock(mtx); // освобождает при выходе из блока никто не будет менять 
            if (stopped) return;   // если очередь закрыта – не добавлянм элы выходим
            q.push(std::move(value)); //добавляет элемент в очередь   можно переехать элементу без копии 
        }
        cond.notify_one();         // будим один ожидающий поток
    }

    // Потокобезопасное извлечение
    // Возвращает false, если очередь закрыта и пуста
    bool pop(T& value) { // тру получен фолс закрыт 
        unique_lock<mutex> lock(mtx);// похож на гвард но нужен тут из-за wait
        cond.wait(lock, [this]() {// поток засыпает пока не станет истиным условие отпускает мтх
            return stopped || !q.empty();// условие пробуждения если закрыта или не пуста  
        });

        if (q.empty() && stopped) {
            return false; // данных нет и очередь закрыта
        }

        value = std::move(q.front());
        q.pop(); //удаляем элемент из очереди
        return true;
    }

    // Закрываем очередь
    void shutdown() { 
        {
            lock_guard<mutex> lock(mtx);
            stopped = true; //флаг  закрыта очередь
        }
        cond.notify_all(); //будит потоки которые ждут 
    }
};

// Производитель: генерирует числа
void producer(ThreadSafeQueue<int>& queue, int count) {
    for (int i = 0; i < count; ++i) {
        this_thread::sleep_for(chrono::milliseconds(10)); // засыпает на 10 милисекунд
        cout << "Producer: " << i << endl; //выводим в консоль что произвели значение i
        queue.push(i); //кладём в очередь
    }
    queue.shutdown(); // после генерации закрываем очередь
}

// Потребитель: забирает числа и "обрабатывает"
void consumer(ThreadSafeQueue<int>& queue, int id) { //забирает числа из очереди и обрабатывает
    int value;
    while (queue.pop(value)) { // возвращает true и записывает очередное число в value или наоборот фолс пустая закрыта
        cout << "Consumer " << id << " got " << value << endl;
        this_thread::sleep_for(chrono::milliseconds(30)); 
    }
    cout << "Consumer " << id << " finished." << endl;
}

int main() {
    setupConsole();

    ThreadSafeQueue<int> q; //объект потокобезопасной очереди

    thread prod(producer, ref(q), 20); // 1 производитель, 20 чисел
    thread c1(consumer, ref(q), 1); //реф ссылка 
    thread c2(consumer, ref(q), 2);
    thread c3(consumer, ref(q), 3);

    prod.join();
    c1.join();
    c2.join();
    c3.join();

    return 0;
}
