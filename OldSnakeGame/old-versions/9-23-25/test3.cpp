#include <iostream>
#define bruh int
#define fax std::cout

int main() {

    bruh thing{ 0 };
    fax << "hello world\n";
    fax << "thing: " << thing << "\n";
    return 0;
}