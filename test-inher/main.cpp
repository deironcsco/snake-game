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

    std::cout << "\n";

    // ope it works first try. cool

    // ITwo** iarr = new ITwo*[]{ s.get(), os.get() }; // this works
    std::unique_ptr<ITwo*[]> bruharr;
    bruharr = std::make_unique<ITwo*[]>(size);
    bruharr[0] = s.get();
    bruharr[1] = os.get();
    for ( int i{ 0 }; i < size; i++ ) {
        bruharr[i]->vfunc();
        bruharr[i]->vfuncTwo();
    }

    std::unique_ptr<int> bruh;
    bruh = std::make_unique<int>( 5 );

    std::unique_ptr<int[]> bruhv;
    bruhv = std::make_unique<int[]>( 2 );
    bruhv[0] = 1;
    bruhv[1] = 2;
    for (int i{ 0 }; i < 2; i ++ ) {
        std::cout << "bruh " << i << " " << bruhv[i] << "\n";
    }
    
    return 0;
}