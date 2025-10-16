#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Book { string title; string author; int year; double price; };

void printBooks(Book* books, int n) 
{
    for (int i = 0; i < n; ++i)
        cout << i + 1 << ") " << books[i].title << " — " << books[i].author
        << ", " << books[i].year << ", " << books[i].price << "\n";
}
void printMostExpensive(Book* books, int n) 
{
    if (n <= 0) return;
    int idx = 0;
    for (int i = 1; i < n; ++i) if (books[i].price > books[idx].price) idx = i;
    cout << "Most expensive: " << books[idx].title << " — " << books[idx].author
        << ", " << books[idx].year << ", " << books[idx].price << "\n";
}

int main() 
{
    int N; cout << "Number of books: ";
    if (!(cin >> N) || N <= 0) return 0;
    Book* books = new Book[N];
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < N; ++i) {
        cout << "Title: "; getline(cin, books[i].title);
        cout << "Author: "; getline(cin, books[i].author);
        cout << "Year: "; cin >> books[i].year;
        cout << "Price: "; cin >> books[i].price;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nLibrary:\n"; printBooks(books, N);
    printMostExpensive(books, N);

    delete[] books;
    return 0;
}
