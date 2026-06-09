#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Style.h"
#include "Bound.h"
#include "GameState.h"
#include <string> // TODO make sure includes are sorted in each file
#include "GameState.h"
#include "Window.h"
#include <memory>

// TODO move to own header file
// Control is because idk how to make whatever argument list you want for
// ...virtual function onClick, so we just putting all game info here so 
// ...if the buttons need it they can have it all as one struct. yeah?
struct Control {
    GameState& gs;
    Window& w;
};

struct ButtonParams {
public:
    sf::Vector2f background_size;
    sf::Vector2f text_size;
    unsigned int font_size;
    sf::String text;
    sf::Font font;
    sf::Vector2f position;
    sf::Color background_color;
    sf::Color outline_color;
    float outline_thickness;
    Control ctrl;
};

class Button : public sf::Drawable {
private:
    // background object
    sf::Vector2f background_size;
    sf::RectangleShape background;

    // text object
    sf::Vector2f text_size;
    sf::Text text;
    
    // boundaries
    // origin +- half of size
    Bound bnd;
    
    Control ctrl;

public:
    Button( ButtonParams* ); // constructor
    bool inBounds( int, int ); // is in bounds, calls Bound::inBounds()
    
    // getters 
    sf::RectangleShape& getBg(); 
    sf::Text& getText(); 

    // drawable  
    void draw( sf::RenderTarget&, sf::RenderStates ) const override;
    
    virtual void onClick( Control ) = 0; // functionality for if clicked
};

#endif