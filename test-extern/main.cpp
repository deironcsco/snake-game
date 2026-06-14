// g++ ./test-extern/main.cpp ./test-extern/test.cpp -I./test-extern -o ./test-extern/te.exe
// ./test-extern/te.exe

#include <iostream>
#include "test.h"

//int value { 5 }; // AHHH i have to init it in global scope?

//using namespace test; // yeah i don't think this works?

int main() {
    std::cout << "hello world\n";

    //int value { 5 }; // initted here, declared in test.h
    //test::value = 5; // can't use {}. because duh
    ::value = 5;

    // test::func(); // declared in test.h, defined in test.cpp
    func();
    
    // if i don't init it at all?
    //      ld error

    // what if i ns it?
    //      same error as before


    return 0;
}