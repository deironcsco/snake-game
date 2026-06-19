#ifndef OBJECT_REGISTRY_H
#define OBJECT_REGISTRY_H

#include <SFML/Graphics.hpp>

#include "Object.h"
#include "GameState.h"
#include "Control.h"

class ObjectRegistry : public sf::Drawable {
private:
    std::vector<Object *> objs; // currently registered objects
    // we'll try a vector but we might need to do std::unique_ptr<Object*[]> objs
    // int size; // size of objs // uncomment if std::vector is good
    Control* ctrl; // reference to game state
public:
    ObjectRegistry(); // constructor
    void draw( sf::RenderTarget& target, sf::RenderStates state ); // TODO headers should include names of params
    // TODO why can't i override
    void registerObject( Object* obj );
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position );
    void handleHover( sf::Vector2i mouse_position );
};


#endif