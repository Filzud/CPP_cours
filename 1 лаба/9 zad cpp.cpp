#include <iostream>
using namespace std;

struct Account { int number; double balance; };
void deposit(Account* acc, double amount) 
{
    if (!acc || amount < 0) return;
    acc->balance += amount;
}

void withdraw(Account& acc, double amount) 
{
    if (amount < 0) return;
    if (acc.balance >= amount) acc.balance -= amount;
    else cout << "Not enough funds\n";
}

int main() 
{
    Account acc{ 12345, 1000.0 };
    cout << acc.number << " " << acc.balance << "\n";
    deposit(&acc, 250.0);
    cout << acc.balance << "\n";
    withdraw(acc, 500.0);
    cout << acc.balance << "\n";
    withdraw(acc, 1000.0);
    cout << acc.balance << "\n";
    return 0;
}
