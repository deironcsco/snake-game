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
    bool flag{ false }; // can only hover over one thing at a time, right?
    for ( int i{ 0 }; i < objs.size(); i++ ) {
        flag = objs[i]->handleHover( mouse_position );
        if ( flag ) {
            break;
        }
    }  
    if ( !flag && !ctrl->window->getCursorIsArrow() ) {
        // reset to default if no hover
        ctrl->window->setCursorArrow( ctrl->window->getWindow() );
    }
};



// getter

Control* ObjectRegistry::getCtrl() {
    return ctrl;
}