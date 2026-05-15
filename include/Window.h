#ifndef window_h // header guard? 
#define window_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Window : public sf::RenderWindow {
private:
    // sf::RenderWindow window; // sfml window instance
    unsigned int window_grid_size; // e.g. 12x12 grid
    unsigned int window_size_px { 600 }; // pixel size of window
    int square_size; // pixel size of square
    bool cursor_is_arrow; // true if cursor is arrow
public:
    Window(unsigned int); // constructor
    // sf::RenderWindow& getWindow();
    template <typename T> T getSquareSize();
    void setCursorIsArrow(bool);
    bool getCursorIsArrow();
};

#endif