#include "ObjectRegistry.h"



// constructor

ObjectRegistry::ObjectRegistry( Control* s_ctrl) : ctrl( s_ctrl ) {};



// funcs

void ObjectRegistry::draw( sf::RenderTarget& target, sf::RenderStates state ) const {
    for ( int i{ 0 }; i < objs.size(); i++ ) {
        if ( *( ctrl->game_state ) == objs[i]->getDrawCondition() ) {
            target.draw( *objs[i], state );
        }
    }
};

void ObjectRegistry::registerObject( Object* obj ) {
    objs.push_back( obj );
};

void ObjectRegistry::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    for ( int i{ 0 }; i < objs.size(); i++ ) {
        objs[i]->handleEvent( event, mouse_position );
    }
};

void ObjectRegistry::handleHover( sf::Vector2i mouse_position ) {
    bool hovering{ false }; // can only hover over one thing at a time, right?. flag == 
    for ( int i{ 0 }; i < objs.size(); i++ ) {
        hovering = objs[i]->handleHover( mouse_position );
        if ( hovering ) {
            break;
        }
    }  
    if ( !hovering && ( ctrl->window->getCursor() != sf::Cursor::Type::Arrow ) ) {
        // reset to default if no hover
        ctrl->window->setCursor( sf::Cursor::Type::Arrow );
    }
};



// getter

Control* ObjectRegistry::getCtrl() {
    return ctrl;
}