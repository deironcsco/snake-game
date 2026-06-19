#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object : public sf::Drawable {
public:
    void virtual handleEvent(std::optional<sf::Event> event, sf::Vector2i mouse_position) = 0;
    bool virtual handleHover(sf::Vector2i mouse_position) = 0;
    GameState virtual getDrawCondition();
};

#endif