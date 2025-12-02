#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string title, author, isbn;
    int year;
    bool available;
public:
    Book(string t, string a, string i, int y) :title(t), author(a), isbn(i), year(y), available(true) {}
    string getIsbn() const { return isbn; }
    string getTitle() const { return title; }
    bool isAvailable() const { return available; }
    void borrow() { if (available) available = false; }
    void returnBook() { available = true; }
    void displayInfo() const {
        cout << title << ", " << author << ", " << isbn << ", " << year << ", " << (available ? "доступна" : "выдана") << endl;
    }
};

class Library {
private:
    string name, address;
    vector<Book> books;
public:
    Library(string n, string addr) :name(n), address(addr) {}
    void addBook(const Book& b) { books.push_back(b); }
    void removeBook(const string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) { if (it->getIsbn() == isbn) { books.erase(it); break; } }
    }
    int findBook(const string& title) const {
        for (size_t i = 0; i < books.size(); ++i) if (books[i].getTitle() == title) return (int)i;
        return -1;
    }
    void borrowBook(const string& isbn) {
        for (auto& b : books) if (b.getIsbn() == isbn) { b.borrow(); break; }
    }
    void returnBookByIsbn(const string& isbn) {
        for (auto& b : books) if (b.getIsbn() == isbn) { b.returnBook(); break; }
    }
    void displayAllBooks() const { for (const auto& b : books) b.displayInfo(); }
    void displayAvailableBooks() const { for (const auto& b : books) if (b.isAvailable()) b.displayInfo(); }
};

int main() 

{
    setlocale(LC_ALL, "rus");
    Library lib("Городская", "ул. Ленина, 1");
    lib.addBook(Book("C++", "Страуструп", "111", 2013));
    lib.addBook(Book("Алгоритмы", "Кормен", "222", 2009));
    lib.displayAllBooks();
    lib.borrowBook("111");
    lib.displayAvailableBooks();
    lib.returnBookByIsbn("111");
    lib.displayAllBooks();
    return 0;
}
