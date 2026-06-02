#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Window object to group some non-game logic / setup
// e.g. size of window, changing cursor 

class Window {
private:
    sf::RenderWindow window; // sfml window instance
    unsigned int window_grid_size; // grid size e.g. 12x12 grid
    unsigned int window_size_px; // pixel size of window
    int square_size; // pixel size of square
    bool cursor_is_arrow{ true }; // true if cursor is arrow
public:
    Window( unsigned int, unsigned int ); // constructor
    
    // getters
    sf::RenderWindow& getWindow();
    template<typename T> T getSquareSize() {
        return (T)square_size;
    }
    bool getCursorIsArrow();
    
    // setters
    // TODO abstract out and create an enumerated for arrow, hand, etc.
    void setCursorArrow( sf::RenderWindow& );
    void setCursorHand( sf::RenderWindow& );
};

#endif