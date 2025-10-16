#include <iostream>
#include <cmath>
using namespace std;

struct Complex { double re; double im; };

Complex add(Complex a, Complex b) { return { a.re + b.re, a.im + b.im }; }
Complex subtract(Complex a, Complex b) { return { a.re - b.re, a.im - b.im }; }
Complex multiply(Complex a, Complex b) { return { a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re }; }

void print(Complex c) 
{
    cout << "(" << c.re;
    if (c.im >= 0) cout << " + " << c.im << "i)";
    else cout << " - " << fabs(c.im) << "i)";
}

int main() 
{
    Complex a, b;
    cout << "a (re im): "; cin >> a.re >> a.im;
    cout << "b (re im): "; cin >> b.re >> b.im;
    Complex s = add(a, b);
    Complex d = subtract(a, b);
    Complex m = multiply(a, b);
    cout << "Sum: "; print(s); cout << "\n";
    cout << "Diff: "; print(d); cout << "\n";
    cout << "Mult: "; print(m); cout << "\n";
    return 0;
}
