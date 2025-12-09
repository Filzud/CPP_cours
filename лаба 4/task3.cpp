#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
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

class ImageProcessor {
private:
    vector<vector<int>> image; // двумерный вектор 1. строки изображения 2. пиксели в строке
    int width;
    int height;

    // Блюр по окну 3x3 с усреднением соседей линейный фильтр усреднения
    int blurPixel(int x, int y, const vector<vector<int>>& src) { //src — исходное изображение, откуда читаем яркости
        int sum = 0;
        int count = 0;

        for (int dy = -1; dy <= 1; ++dy) { //смещение по вертикале 
            for (int dx = -1; dx <= 1; ++dx) { //горизонт
                int nx = x + dx; //координаты соседей
                int ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    sum += src[ny][nx]; //добавляем яркость соседнего пикселя
                    ++count; //увелич соседей
                }
            }
        }
        return sum / count; //сум суммая яркостей на количество
    }

    // Обработка полосы строк [y_start; y_end) горизонт
    void processStrip(int y_start, int y_end,
                      const vector<vector<int>>& src,
                      vector<vector<int>>& dst) {  //dst — целевое изображение (туда записываем резы)
        for (int y = y_start; y < y_end; ++y) { //внешний цикл по строкам
            for (int x = 0; x < width; ++x) { //внутренний цикл по стобам
                // Границы не блюрим
                if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
                    dst[y][x] = src[y][x]; //оставляем как есть
                } else {
                    dst[y][x] = blurPixel(x, y, src); //новый рез в дст
                }
            }
        }
    }

public:
    ImageProcessor(int w, int h) : width(w), height(h) { //инициализируем
        image.assign(height, vector<int>(width, 0)); //все яркости 0 чёрное

        mt19937 gen(random_device{}()); //генератор случ чисел
        uniform_int_distribution<int> dist(0, 255);

        // Заполняем случайными яркостями
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                image[y][x] = dist(gen); // 0-255
            }
        }
    }

    void applyFilterSingleThread() {//размыть в одном потоке
        vector<vector<int>> src = image;
        vector<vector<int>> result = image;
        processStrip(0, height, src, result); //обработка всей картинки полосой от 0 до высоты
        image = std::move(result);//мув быстрый
    }

    void applyFilterMultiThread(int num_threads) { 
        if (num_threads <= 0) num_threads = 1;

        vector<vector<int>> src = image;
        vector<vector<int>> result = image;
        vector<thread> threads; //вектор потоков

        int rows_per_thread = height / num_threads;//скок строк каждому потоку
        int y_start = 0;

        for (int i = 0; i < num_threads; ++i) {
            int y_end = (i == num_threads - 1) ? height : y_start + rows_per_thread;

            threads.emplace_back(&ImageProcessor::processStrip,
                                 this, y_start, y_end,
                                 cref(src), ref(result)); //креф константа ток читают

            y_start = y_end;
        }

        for (auto& t : threads) {
            t.join();
        }

        image = std::move(result);
    }

    double averageBrightness() const {//средн яркость
        long long sum = 0;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                sum += image[y][x];
            }
        }
        return static_cast<double>(sum) / (width * height); //средняя яркость
    }
};

int main() {
    setupConsole();

    ImageProcessor img(800, 600);

    auto start_single = chrono::steady_clock::now();
    img.applyFilterSingleThread(); //размываем
    auto end_single = chrono::steady_clock::now();

    auto start_multi = chrono::steady_clock::now();
    img.applyFilterMultiThread(4);
    auto end_multi = chrono::steady_clock::now();

    auto time_single = chrono::duration_cast<chrono::milliseconds>(end_single - start_single).count();
    auto time_multi  = chrono::duration_cast<chrono::milliseconds>(end_multi - start_multi).count();

    cout << "Размытие (1 поток): " << time_single << " мс\n";
    cout << "Размытие (4 потока): " << time_multi  << " мс\n";
    cout << "Средняя яркость: " << img.averageBrightness() << "\n";

    return 0;
}
