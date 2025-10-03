#include <iostream>
#include <cmath>

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout.setf(std::ios::fixed);
    std::cout.precision(6);

    const double PI = 3.14159265358979323846;

    while (true) {
        std::cout << "\n1) +  2) -  3) *  4) /  5) pow  6) sqrt  7) sin  8) cos  9) tan  10) ln  11) log10  0) exit\n";
        std::cout << "выбери действие) ";
        int c;
        if (!(std::cin >> c)) return 0;
        if (c == 0) break;

        double a, b, r;

        switch (c) {
        case 1:
            std::cout << "a b: ";
            std::cin >> a >> b;
            r = a + b;
            std::cout << r << "\n";
            break;
        case 2:
            std::cout << "a b: ";
            std::cin >> a >> b;
            r = a - b;
            std::cout << r << "\n";
            break;
        case 3:
            std::cout << "a b: ";
            std::cin >> a >> b;
            r = a * b;
            std::cout << r << "\n";
            break;
        case 4:
            std::cout << "a b: ";
            std::cin >> a >> b;
            if (b == 0) { std::cout << "err\n"; break; }
            r = a / b;
            std::cout << r << "\n";
            break;
        case 5:
            std::cout << "a b (a^b): ";
            std::cin >> a >> b;
            r = std::pow(a, b);
            std::cout << r << "\n";
            break;
        case 6:
            std::cout << "a: ";
            std::cin >> a;
            if (a < 0) { std::cout << "err\n"; break; }
            r = std::sqrt(a);
            std::cout << r << "\n";
            break;
        case 7:
            std::cout << "x (deg): ";
            std::cin >> a;
            r = std::sin(a * PI / 180.0);
            std::cout << r << "\n";
            break;
        case 8:
            std::cout << "x (deg): ";
            std::cin >> a;
            r = std::cos(a * PI / 180.0);
            std::cout << r << "\n";
            break;
        case 9:
            std::cout << "x (deg): ";
            std::cin >> a;
            if (std::fmod(std::fabs(a - 90.0), 180.0) < 1e-12) { std::cout << "err\n"; break; }
            r = std::tan(a * PI / 180.0);
            std::cout << r << "\n";
            break;
        case 10:
            std::cout << "a: ";
            std::cin >> a;
            if (a <= 0) { std::cout << "err\n"; break; }
            r = std::log(a);
            std::cout << r << "\n";
            break;
        case 11:
            std::cout << "a: ";
            std::cin >> a;
            if (a <= 0) { std::cout << "err\n"; break; }
            r = std::log10(a);
            std::cout << r << "\n";
            break;
        default:
            std::cout << "?\n";
        }
    }
    return 0;
}
