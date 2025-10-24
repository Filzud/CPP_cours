#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber, ownerName;
    double balance;
    static int totalAccounts;
    static double totalBankBalance;
    const double MIN_BALANCE = 10.0;
public:
    BankAccount(string num, string owner, double bal) :accountNumber(num), ownerName(owner), balance(bal) {
        totalAccounts++; totalBankBalance += balance;
    }
    ~BankAccount() { totalAccounts--; totalBankBalance -= balance; }
    void deposit(double amount) { if (amount > 0) { balance += amount; totalBankBalance += amount; } }
    void withdraw(double amount) {
        if (amount > 0 && balance - amount >= MIN_BALANCE) { balance -= amount; totalBankBalance -= amount; }
    }
    void displayAccountInfo() const {
        cout << accountNumber << ", " << ownerName << ", " << balance << endl;
    }
    static int getTotalAccounts() { return totalAccounts; }
    static double getTotalBankBalance() { return totalBankBalance; }
    static double getAverageBalance() { return totalAccounts ? totalBankBalance / totalAccounts : 0.0; }
};
int BankAccount::totalAccounts = 0;
double BankAccount::totalBankBalance = 0.0;

int main() 
{
    setlocale(LC_ALL, "rus");
    BankAccount a("A1", "Иван", 100), b("B2", "Ольга", 250);
    a.deposit(50); b.withdraw(30);
    a.displayAccountInfo(); b.displayAccountInfo();
    cout << BankAccount::getTotalAccounts() << endl;
    cout << BankAccount::getTotalBankBalance() << endl;
    cout << BankAccount::getAverageBalance() << endl;
    return 0;
}
