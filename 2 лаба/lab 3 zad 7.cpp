#include <iostream>
using namespace std;

class Complex {
private:
    double real, imaginary;
public:
    Complex(double r = 0, double i = 0) :real(r), imaginary(i) {}
    double re() const { return real; }
    double im() const { return imaginary; }
    void setRe(double r) { real = r; }
    void setIm(double i) { imaginary = i; }
    Complex operator+(const Complex& o) const { return Complex(real + o.real, imaginary + o.imaginary); }
    Complex operator-(const Complex& o) const { return Complex(real - o.real, imaginary - o.imaginary); }
    Complex operator*(const Complex& o) const { return Complex(real * o.real - imaginary * o.imaginary, real * o.imaginary + imaginary * o.real); }
    bool operator==(const Complex& o) const { return real == o.real && imaginary == o.imaginary; }
    friend ostream& operator<<(ostream& os, const Complex& c) { os << c.real << " + " << c.imaginary << "i"; return os; }
    friend istream& operator>>(istream& is, Complex& c) { is >> c.real >> c.imaginary; return is; }
};

int main() {
    Complex a(2, 3), b(1, 4);
    cout << (a + b) << endl;
    cout << (a - b) << endl;
    cout << (a * b) << endl;
    Complex c; cin >> c; cout << c << endl;
    return 0;
}
