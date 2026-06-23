#ifndef OBJECT_REGISTRY_H
#define OBJECT_REGISTRY_H

#include <SFML/Graphics.hpp>

#include "Object.h"
#include "GameState.h"
#include "Control.h"

class ObjectRegistry : public sf::Drawable {
private:
    std::vector<Object *> objs; // currently registered objects
    Control* ctrl; // reference to control objects
public:
    ObjectRegistry( Control* );
    void draw( sf::RenderTarget& target, sf::RenderStates state ) const override; // TODO in all header files - headers should include names of params
    void registerObject( Object* obj ); // TODO could this be an unpack so i can do multiple at once?
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position );
    void handleHover( sf::Vector2i mouse_position );
    
    // getter
    Control* getCtrl(); // created because segfault issue with ctrl uninitialized
};


#endif