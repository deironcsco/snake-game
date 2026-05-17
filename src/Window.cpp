#include "../include/Window.h"
#include <iostream>

// implementation file for Window

Window::Window( unsigned int s_window_grid_size, unsigned int s_window_size_px ) : 
window_grid_size( s_window_grid_size ),
window_size_px( s_window_size_px ) { 
    square_size = window_size_px / window_grid_size;

    window = { sf::VideoMode( sf::Vector2u{ window_size_px, window_size_px } ), "Snake" };
    
    // disable manipulating window size (cuz it fucks with graphics)
    window.setMinimumSize( std::optional { sf::Vector2u{ window_size_px, window_size_px } } );
    window.setMaximumSize( std::optional { sf::Vector2u{ window_size_px, window_size_px } } );

    bool cursor_is_arrow{ true }; // for cursor being arrow
};



// getters
sf::RenderWindow& Window::getWindow() {
    return window;
};

// TODO just do get cursor value
bool Window::getCursorIsArrow() {
    return cursor_is_arrow;
};



// setters
void Window::setCursorArrow( sf::RenderWindow& rw ) {
    const auto cursor = sf::Cursor::createFromSystem( sf::Cursor::Type::Arrow ).value(); //.value() because optional. have to make a cursor before passing to window
    rw.setMouseCursor( cursor );
    cursor_is_arrow = true;
}

void Window::setCursorHand( sf::RenderWindow& rw ) {
    const auto cursor = sf::Cursor::createFromSystem( sf::Cursor::Type::Hand ).value(); //.value() because optional. have to make a cursor before passing to window
    rw.setMouseCursor( cursor );
    cursor_is_arrow = false;
}

