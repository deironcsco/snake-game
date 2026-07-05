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
    void draw( sf::RenderTarget& target, sf::RenderStates state ) const override;
    void registerObject( Object* obj ); 
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position );
    void handleHover( sf::Vector2i mouse_position );
    
    // getter
    Control* getCtrl(); // created because segfault issue with ctrl uninitialized
};


#endif