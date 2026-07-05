#include <iostream>

void func();


// i need an interface, a second interface that comes from the first, and something to instantiate both interfaces


class IOne {
public:
    void virtual vfunc() = 0;
};

class ITwo : public IOne {
public:
    void virtual vfuncTwo() = 0;
};

class Stuff : public ITwo {
public:
    Stuff() = default;
    void vfunc() override {
        std::cout << "virtual func 1\n";
    }
    void vfuncTwo() override {
        std::cout << "virtual func 2\n";
    }
};

class OtherStuff : public ITwo {
public:
    OtherStuff() = default;
    void vfunc() override {
        std::cout << "other virtual func 1\n";
    }
    void vfuncTwo() override {
        std::cout << "other virtual func 2\n";
    }
};
