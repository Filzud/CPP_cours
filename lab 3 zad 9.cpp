#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

template<typename T>
class Stack {
private:
    vector<T> elements;
    int cap;
public:
    Stack(int size = 10) :cap(size) {}
    void push(const T& e) { if ((int)elements.size() == cap) throw runtime_error("full"); elements.push_back(e); }
    T pop() { if (elements.empty()) throw runtime_error("empty"); T v = elements.back(); elements.pop_back(); return v; }
    T top() const { if (elements.empty()) throw runtime_error("empty"); return elements.back(); }
    bool isEmpty() const { return elements.empty(); }
    bool isFull() const { return (int)elements.size() == cap; }
    int size() const { return (int)elements.size(); }
    void display() const { for (const auto& x : elements) cout << x << " "; cout << endl; }
};

template<typename T>
class Queue {
private:
    vector<T> elements;
    int cap;
public:
    Queue(int size = 10) :cap(size) {}
    void enqueue(const T& e) { if ((int)elements.size() == cap) throw runtime_error("full"); elements.push_back(e); }
    T dequeue() { if (elements.empty()) throw runtime_error("empty"); T v = elements.front(); elements.erase(elements.begin()); return v; }
    T front() const { if (elements.empty()) throw runtime_error("empty"); return elements.front(); }
    bool isEmpty() const { return elements.empty(); }
    bool isFull() const { return (int)elements.size() == cap; }
    int size() const { return (int)elements.size(); }
};

int main() {
    Stack<int> si(3); si.push(1); si.push(2); si.display(); cout << si.pop() << endl;
    Queue<string> qs(3); qs.enqueue("a"); qs.enqueue("b"); cout << qs.front() << endl; cout << qs.dequeue() << endl;
    return 0;
}
