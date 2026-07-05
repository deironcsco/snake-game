#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

#include "GameState.h"

class Object : public sf::Drawable {
public:
    // what the object wants to do with events (e.g. if it's clickable)
    void virtual handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) = 0;
    // does the cursor change over hover? true if changed, false if unchanged
    bool virtual handleHover( sf::Vector2i mouse_position ) = 0;
    // what GameState does the object appear in
    GameState virtual getDrawCondition() = 0;
    
    // NOTE: remember Objects also have to implement sf::Drawable::draw
};

#endif