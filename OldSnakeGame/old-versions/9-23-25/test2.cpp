#include <iostream>
#include <vector>

int main() {
    /*
    std::vector<int> v{1,2,3,4};
    for (int i{ 0 }; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n\n";
    std::cout << v[v.size()-1] << "\n";
    */

    unsigned int x{ 10 };
    std::cout << x << "\n";
    std::cout << -(int)x << "\n";
    int y { 10 };
    std::cout << y << "\n";
    std::cout << -y << "\n";

    return 0;
}