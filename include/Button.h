#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Style.h"
#include "Bound.h"
#include "Control.h"
#include "GameState.h"
#include "GameState.h"
#include "Window.h"
#include "Object.h"

// inherit from Object

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
};

class Button : public Object {
protected:
    // background object
    sf::Vector2f background_size;
    sf::RectangleShape background;

    // text object
    sf::Vector2f text_size;
    sf::Text text;
    
    // boundaries
    // origin +- half of size
    Bound bnd;
    
    Control* ctrl;

public:
    Button( ButtonParams*, Control* ); // constructor
    bool inBounds( sf::Vector2i ); // is in bounds, calls Bound::inBounds()
    
    // getters 
    sf::RectangleShape& getBg(); 
    sf::Text& getText(); 

    // drawable  
    void draw( sf::RenderTarget&, sf::RenderStates ) const override;

    // Object overrides
    bool handleHover(sf::Vector2i mouse_position) override;
    GameState virtual getDrawCondition() override;
    void virtual handleEvent(std::optional<sf::Event> event, sf::Vector2i mouse_position) override;

    // virtual
    void virtual onClick() = 0;
};

#endif