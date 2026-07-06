#ifndef TEXT_H
#define TEXT_H

#include "Object.h"

// Text is kinda just a wrapper for sf::Text that interfaces with Object
// just to display some text on the screen

struct TextParams {
    sf::Vector2f position;
    unsigned int text_size;
    sf::Vector2f size;
    sf::Font font;
    sf::String text;
};



class Text : public Object {
private:
    sf::Text text;          // text object

    sf::Vector2f position;  // position of the object on the screen 
    sf::Vector2f size;      // the x and y size (not bounds)
public:
    Text( TextParams& );
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) override;
    void draw( sf::RenderTarget&, sf::RenderStates ) const override;

    // NOTE: components still need to implement Object::handleHover and Object::getDrawCondition
};


#endif