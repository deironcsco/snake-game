#include "../include/Window.h"
#include <iostream>


Window::Window(unsigned int s_window_grid_size): 
    sf::RenderWindow{ sf::VideoMode( sf::Vector2u{ window_size_px, window_size_px } ), "Snake" }, 
    window_grid_size(s_window_grid_size) {
    std::cout << "wsp" << window_size_px << "\n";
    
    square_size = window_size_px / window_grid_size;
    
    // window = { sf::VideoMode( sf::Vector2u{ window_size_px, window_size_px } ), "Snake" };
    
    
    // disable manipulating window size (cuz it fucks with graphics)
    this->setMinimumSize( std::optional { sf::Vector2u{ window_size_px, window_size_px } } );
    this->setMaximumSize( std::optional { sf::Vector2u{ window_size_px, window_size_px } } );


    bool cursor_is_arrow{ true }; //for cursor being arrow
};

// sf::RenderWindow& Window::getWindow() {
//     return window;
// };

template<typename T>
T Window::getSquareSize() {
    return (T)square_size;
}

void Window::setCursorIsArrow(bool val) {
    cursor_is_arrow = val;
};

bool Window::getCursorIsArrow() {
    return cursor_is_arrow;
};