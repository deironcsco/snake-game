#include "../../include/test/TestWindow.h"
#include "../../include/Window.h"
#include "../../include/Exception.h"
#include <SFML/Graphics.hpp>
#include <iostream>


// TODO can i template out the console outputs? auto add \ts and \ns and all that
// and printing the names and stuff

// only testing the constructor. everything else is getters and setters
// constructor only does what?
// calculates square size, creates a window, and sets size
void TestWindow() {
    // happy paths
    TestWindow_ShouldInstantiateWhenInputsArePositive();

    // sad paths
    // 0 and 0
    TestWindow_ShouldNotInstantiateWhenInputsZero();
}

void TestWindow_ShouldInstantiateWhenInputsArePositive() {
    std::cout << "TestWindow_ShouldInstantiateWhenInputsArePositive\n";

    // create window
    Window w{ 12, 600 };

    // assert square size 
    if ( w.getSquareSize<int>() != 50 ) {
        std::cout << "\tFAIL Window SquareSize is incorrect\n";
        return;
    }

    // assert window size
    sf::Vector2u v { w.getWindow().getSize() };
    if ( v.x != 600 ) {
        std::cout << "\tFAIL Window WindowSize x is incorrect!\n";
        return;
    }
    if ( v.y != 600 ) {
        std::cout << "\tFAIL Window WindowSize y is incorrect!\n";
        return;
    }
    // TODO should we throw errors
    std::cout << "\tAll good!\n";
    return;
}

void TestWindow_ShouldNotInstantiateWhenInputsZero() {
    std::cout << "TestWindow_ShouldNotInstantiateWhenInputsZero\n";
    
    // create window, catch error
    try {
        Window w{ 0, 0 };
    } catch( DivideByZeroException e ) {
        std::cout << "\tAll good!";
        return;
    } catch( ... ) {
        std::cout << "\tFAIL No Divide By Zero Exception\n";
    }
    return;
}