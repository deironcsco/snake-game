#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Style.h"
#include "Bound.h"
#include "GameState.h"
#include <string> // TODO make sure includes are sorted in each file

struct ButtonParams {
public:
    sf::Vector2f background_size;
    sf::Vector2f text_size;
    unsigned int font_size;
    std::string text;
    sf::Font font;
    sf::Vector2f position;
    sf::Color background_color;
    sf::Color outline_color;
    float outline_thickness;
};

class Button : public sf::Drawable {
private:
    // background object
    sf::Vector2f background_size{ 150, 100 };
    sf::RectangleShape background{ background_size };

    // text object
    sf::Vector2f text_size{ 80, 30 };
    sf::Text text{ font, "START", normal_text_size };
    
    // boundaries
    // origin +- half of size
    Bound bnd = {
        button_position.x + background_size.x / 2,
        button_position.x - background_size.x / 2,
        button_position.y + background_size.y / 2,
        button_position.y - background_size.y / 2,
    };

public:
    Button(); // constructor
    bool inBounds( int, int ); // is in bounds, calls Bound::inBounds()
    
    // getters 
    sf::RectangleShape& getBg(); 
    sf::Text& getText(); 

    // drawable  
    void draw( sf::RenderTarget&, sf::RenderStates ) const override;
    
    virtual void onClick( GameState& ) = 0; // functionality for if clicked
};

#endif