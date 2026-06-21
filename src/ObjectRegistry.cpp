#include "ObjectRegistry.h"

ObjectRegistry::ObjectRegistry() = default; // constructor

void ObjectRegistry::draw( sf::RenderTarget& target, sf::RenderStates state ) const {
    for ( int i{ 0 }; i < objs.size(); i++ ) {
        if ( *( ctrl->gs ) == objs[i]->getDrawCondition() ) {
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
    if ( !flag ) {
        // reset to default if no hover
        ctrl->w->setCursorArrow( ctrl->w->getWindow() );
    }
};



/*
handleHover(mouse_pos) {
Flag false
For (size)
Flag = Objs[size]->handleBounds(mouse)
If flag break // if i’m hovering over one thing i don’t care about other thing. probably
If !flag
Reset cursor
}


*/