#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// #include "ObjectRegistry.h"

// Window object to group some non-game logic / setup
// e.g. size of window, changing cursor 

class ObjectRegistry;


class Window {
private:
    sf::RenderWindow window; // sfml window instance
    unsigned int window_grid_size; // grid size e.g. 12x12 grid
    unsigned int window_size_px; // pixel size of window
    int square_size; // pixel size of square
    sf::Cursor::Type curr_cursor;
public:
    Window( unsigned int, unsigned int ); // constructor

    // rw funcs
    bool isOpen() const; // isOpen is const so...
    std::optional<sf::Event> pollEvent();
    void close();
    void display(ObjectRegistry&); // rw.clear, rw.draw, then rw.display
    
    // getters
    sf::RenderWindow& getRenderWindow();
    template<typename T> T getSquareSize() {
        return (T)square_size;
    }
    sf::Cursor::Type getCursor();
    
    // setters
    void setCursor(sf::Cursor::Type);

};

#endif