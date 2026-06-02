#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Style.h"
#include "Bound.h"
#include "GameState.h"

// The button to start the game in the title screen

class StartButton : public sf::Drawable {
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
    StartButton(); // constructor
    bool inBounds( int, int ); // is in bounds, calls Bound::inBounds()
    
    // getters 
    sf::RectangleShape& getBg(); 
    sf::Text& getText(); 

    // drawable  
    void draw( sf::RenderTarget&, sf::RenderStates ) const override;
    
    void onClick( GameState& ); // functionality for if clicked
};

#endif