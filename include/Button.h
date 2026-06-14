#ifndef BUTTON_H
#define BUTTON_H

#include <string> // TODO make sure includes are sorted in each file
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Style.h"
#include "Bound.h"
#include "Control.h"
#include "GameState.h"
#include "GameState.h"
#include "Window.h"


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
    Control ctrl; // TODO reference to a control?
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
    
    Control ctrl; // TODO make this a pointer

public:
    Button( ButtonParams* ); // constructor
    bool inBounds( int, int ); // is in bounds, calls Bound::inBounds()
    
    // getters 
    sf::RectangleShape& getBg(); 
    sf::Text& getText(); 

    // drawable  
    void draw( sf::RenderTarget&, sf::RenderStates ) const override;
    
    // TODO why do i pass in control when it's a mem var?
    virtual void onClick( Control ) = 0; // functionality for if clicked
};

#endif