#include "ObjectRegistry.h"

// constructor
ObjectRegistry::ObjectRegistry( Control* s_ctrl ) : ctrl( s_ctrl ) {};

// add Object to list
void ObjectRegistry::registerObject( Object* obj ) {
    objs.push_back( obj );
};

// loop through Object::handleEvents
void ObjectRegistry::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    for ( int i{ 0 }; i < objs.size(); i++ ) {
        if ( *( ctrl->game_state ) == objs[i]->getDrawCondition() ) {
            objs[i]->handleEvent( event, mouse_position );
        }
    }
};

// loop through Objects::handleHover
void ObjectRegistry::handleHover( sf::Vector2i mouse_position ) {
    bool hovering{ false }; // can only hover over one thing at a time, right?. flag == 
    for ( int i{ 0 }; i < objs.size(); i++ ) {
        if ( *( ctrl->game_state ) == objs[i]->getDrawCondition() ) {
            hovering = objs[i]->handleHover( mouse_position );
            if ( hovering ) {
                break;
            }
        }
    }  
    if ( !hovering && ( ctrl->window->getCursor() != sf::Cursor::Type::Arrow ) ) {
        // reset to default if no hover
        ctrl->window->setCursor( sf::Cursor::Type::Arrow );
    }
};



// Drawable override
// draw all objects in the list
void ObjectRegistry::draw( sf::RenderTarget& target, sf::RenderStates state ) const {
    for ( int i{ 0 }; i < objs.size(); i++ ) {
        if ( *( ctrl->game_state ) == objs[i]->getDrawCondition() ) {
            target.draw( *objs[i], state );
        }
    }
};



// getter

Control* ObjectRegistry::getCtrl() {
    return ctrl;
}