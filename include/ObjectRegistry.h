#ifndef OBJECT_REGISTRY_H
#define OBJECT_REGISTRY_H

#include <SFML/Graphics.hpp>

#include "Object.h"
#include "GameState.h"
#include "Control.h"

// ObjectRegistry is the main wrapper for all components in the game
// it's here b/c when i add a component I don't also want to jump
// around the file to add it's draw conditions + event handling
// so this takes care of all that so that when I make a new component
// I can bundle all its feature together and let OR handle everything

class ObjectRegistry : public sf::Drawable {
private:
    std::vector<Object *> objs; // currently registered objects
    Control* ctrl;              // reference to control objects
public:
    ObjectRegistry( Control* ); // constructor
    void registerObject( Object* ); // add an object to the list

    // object overrides
    // loop through Object::handleEvent's
    void handleEvent( std::optional<sf::Event>, sf::Vector2i mouse_position );
    // loop through Object::handleHover's
    void handleHover( sf::Vector2i mouse_position );
    void play();

    // Drawable override
    void draw( sf::RenderTarget&, sf::RenderStates ) const override;
    
    // getter
    Control* getCtrl(); // created because segfault issue with ctrl uninitialized
};


#endif