#ifndef startbutton_h
#define startbutton_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Style.h"

// TODO bound struct
// TODO size struct? use sf vector?
// TODO drawable

class StartButton {
private:
    // background object
    float bg_x{ 150 }; // background sizes
    float bg_y{ 100 };
    sf::RectangleShape bg{ { bg_x, bg_y } };

    // text object
    float text_x{ 80 }; // text sizes
    float text_y{ 30 };
    sf::Text text{ font, "START", normal_text_size };
    
    // bounds of button
    float x_lbound; 
    float x_ubound;
    float y_lbound;
    float y_ubound;

public:
    StartButton();
    bool inBounds(int, int);
    sf::RectangleShape& getBg();
    sf::Text& getText();
};

#endif