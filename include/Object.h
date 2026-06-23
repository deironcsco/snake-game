#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

#include "GameState.h"

class Object : public sf::Drawable {
public:
    void virtual handleEvent(std::optional<sf::Event> event, sf::Vector2i mouse_position) = 0;
    bool virtual handleHover(sf::Vector2i mouse_position) = 0;
    GameState virtual getDrawCondition() = 0;
    // remember Objects also have to implement sf::Drawable::draw
};

#endif