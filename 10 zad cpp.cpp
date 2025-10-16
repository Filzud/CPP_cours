#include <iostream>
#include <string>
using namespace std;

struct Book { string title; string author; int year; double price; };

void sortBooksByYear(Book* b, int n) 
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (b[j].year > b[j + 1].year) { Book t = b[j]; b[j] = b[j + 1]; b[j + 1] = t; }
}
Book* findBookByAuthor(Book* b, int n, const string& author) 
{
    for (int i = 0; i < n; ++i) if (b[i].author == author) return &b[i];
    return nullptr;
}

void printBooks(const Book* b, int n) 
{
    for (int i = 0; i < n; ++i)
        cout << i + 1 << ") " << b[i].title << " — " << b[i].author
        << ", " << b[i].year << ", " << b[i].price << "\n";
}
int main() 
{
    int n = 5;
    Book* books = new Book[n]{
        {"C++ Basics", "Stroustrup", 2013, 30.5},
        {"Algorithms", "Sedgewick", 2011, 45.0},
        {"Clean Code", "Martin", 2008, 40.0},
        {"Effective C++", "Meyers", 2005, 35.0},
        {"Modern C++", "Rainer", 2019, 50.0}
    };

    cout << "Before:\n"; printBooks(books, n);
    sortBooksByYear(books, n);
    cout << "After:\n"; printBooks(books, n);

    string author = "Martin";
    Book* f = findBookByAuthor(books, n, author);
    if (f) cout << "Found: " << f->title << ", " << f->year << ", " << f->price << "\n";
    else cout << "Not found\n";

    delete[] books;
    return 0;
}
