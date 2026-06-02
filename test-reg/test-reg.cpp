// g++ ./test-reg/test-reg.cpp -o ./test-reg/a.exe
// ./test-reg/a.exe

#include <iostream>

void func1();
void func2();
int func3();
void func4();
void func5(int, int);
void func6(int, int);
void func7(int, int);
void normal();
void reg();

int main() {
    normal();
    reg();
    return 0;
}

void normal() {
    std::cout << "\nNORMAL\n";
    func1();
    func2();
    func3();
    return;
}

void reg() {
    std::cout << "\nREG\n";
    void (*x)() { *func1 };
    x();

    // how do you make arrays?
    int arr[] = { 1, 2, 3 };
    int* p_arr = new int[3]{ 4, 5, 6};

    int size = 3;
    for (int i { 0 }; i < size; i++ ) {
        std::cout << "i: " << arr[i] << "\n";
        std::cout << "p: " << p_arr[i] << "\n";
    }

    delete[] p_arr;

    // does that work with normal functions?
    auto y{ func3 };
    // not its always <type> (*var)()
    // so how do i make an array of this?
    void (*z[])() { *func1, *func2, *func4 };
    // does it matter if it's a pointer or not?
    size = 3;
    for (int i { 0 }; i < size; i++ ) {
        z[i]();
    }
    // yeah that works. cool

    // what about with parameters?
    std::cout << "\n\n";
    void (*w[])(int, int) { *func5, *func6, *func7 };
    size = 3;
    for (int i{ 0 }; i < size; i++) { 
        w[i](i, i+1);
    }
    // cool
}





void func1() {
    std::cout << "hello\n";
    return;
}

void func2() {
    std::cout << "world\n";
    return;
}

int func3() {
    std::cout << "gamer\n";
    return 1;
}

void func4() {
    std::cout << "gamer\n";
    return;
}

void func5(int x, int y) {
    std::cout << "hello " << x+y << "\n";
    return;
}

void func6(int a, int b) {
    std::cout << "world " << a+b << "\n";
    return;
}

void func7(int c, int e) {
    std::cout << "gamer " << c+e << "\n";
    return;
}