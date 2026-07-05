#include "../include/Window.h"
#include <iostream>
#include "../include/Exception.h"
#include "../include/ObjectRegistry.h"

Window::Window( unsigned int s_window_grid_size, unsigned int s_window_size_px ) : 
window_grid_size( s_window_grid_size ),
window_size_px( s_window_size_px ) { 
    if ( window_grid_size == 0 ) {
        throw DivideByZeroException{};
    }
    square_size = window_size_px / window_grid_size;

    window = { sf::VideoMode( sf::Vector2u{ window_size_px, window_size_px } ), "Snake" };
    
    // disable manipulating window size (cuz it fucks with graphics)
    window.setMinimumSize( std::optional { sf::Vector2u{ window_size_px, window_size_px } } );
    window.setMaximumSize( std::optional { sf::Vector2u{ window_size_px, window_size_px } } );
};


// rw funcs
bool Window::isOpen() const {
    return window.isOpen();
}

std::optional<sf::Event> Window::pollEvent() {
    return window.pollEvent();
}

// TODO - all these funcs inline?
void Window::close() {
    window.close();
    return;
}

void Window::display(ObjectRegistry& obreg) {
    window.clear();
    window.draw(obreg);
    window.display();
    return;
}



// getters
sf::RenderWindow& Window::getRenderWindow() {
    return window;
};


sf::Cursor::Type Window::getCursor() {
    return curr_cursor;
}


// setters
void Window::setCursor(sf::Cursor::Type c) {
    const auto cursor = sf::Cursor::createFromSystem( c ).value(); //.value() because optional. have to make a cursor before passing to window
    window.setMouseCursor( cursor );
    curr_cursor = c;
}


