#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string brand, model;
    int year;
    double fuelLevel;
public:
    Vehicle(string b, string m, int y) :brand(b), model(m), year(y), fuelLevel(100) {}
    virtual ~Vehicle() {}
    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual void refuel(double amount) = 0;
    virtual void displayInfo() const {
        cout << brand << " " << model << " (" << year << ") " << fuelLevel << "%" << endl;
    }
    double getFuelLevel() const { return fuelLevel; }
    void setFuelLevel(double l) { if (l >= 0 && l <= 100) fuelLevel = l; }
};

class Car : public Vehicle {
private:
    int doors;
    string transmission;
public:
    Car(string b, string m, int y, int d, string t) :Vehicle(b, m, y), doors(d), transmission(t) {}
    void startEngine() override { cout << "Car start" << endl; }
    void stopEngine() override { cout << "Car stop" << endl; }
    void refuel(double amount) override { setFuelLevel(min(100.0, fuelLevel + amount)); }
};

class Motorcycle : public Vehicle {
private:
    bool hasFairing;
public:
    Motorcycle(string b, string m, int y, bool f) :Vehicle(b, m, y), hasFairing(f) {}
    void startEngine() override { cout << "Moto start" << endl; }
    void stopEngine() override { cout << "Moto stop" << endl; }
    void refuel(double amount) override { setFuelLevel(min(100.0, fuelLevel + amount)); }
    void wheelie() { cout << brand << " " << model << " делает вилли!" << endl; }
};

int main() {
    vector<Vehicle*> v;
    v.push_back(new Car("Toyota", "Corolla", 2015, 4, "AT"));
    v.push_back(new Motorcycle("Yamaha", "MT-07", 2019, true));
    for (auto p : v) { p->startEngine(); p->displayInfo(); p->refuel(5); p->displayInfo(); p->stopEngine(); }
    for (auto p : v) delete p;
    return 0;
}
