#include <iostream>
#include <memory>
#include "header.h"

// g++ ./test-inher/main.cpp ./test-inher/header.cpp -I./test-inher -o ./test-inher/main.exe
// ./test-inher/main.exe 

int main() {
    std::cout << "hello world\n";
    func();

    std::unique_ptr<Stuff> s = std::make_unique<Stuff>( Stuff{} ); 
    std::unique_ptr<OtherStuff> os = std::make_unique<OtherStuff>( OtherStuff{} );

    // how do i make an array again
    int arr[]{ 1, 2, 3 };

    //i should have an array of ITwo* an loop through their functions
    ITwo* iarr[]{ s.get(), os.get() };
    int size{ 2 };
    for ( int i{ 0 }; i < size; i++ ) {
        iarr[i]->vfunc();
        iarr[i]->vfuncTwo();
    }

    return 0;
}