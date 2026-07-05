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

// Button component

// params to pass into buttons
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
    
    Bound bnd; // boundaries (origin +- half of size)
    
    Control* ctrl; // Control reference

public:
    Button( ButtonParams&, Control* ); // constructor
    bool inBounds( sf::Vector2i mouse_position ); // is in bounds, calls Bound::inBounds()
    void virtual onClick() = 0; // virtual, to handle events

    // Drawable override  
    void draw( sf::RenderTarget&, sf::RenderStates ) const override;

    // Object overrides
    bool handleHover(sf::Vector2i mouse_position) override;
    GameState virtual getDrawCondition() override;
    void virtual handleEvent(std::optional<sf::Event> event, sf::Vector2i mouse_position) override;

    // getters 
    sf::RectangleShape& getBg(); 
    sf::Text& getText(); 
};

#endif