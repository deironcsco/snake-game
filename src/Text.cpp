#include "../include/Text.h"

// constructor
Text::Text( TextParams& tp ) : 
    position( tp.position ),
    size( tp.size ),
    text( tp.font, tp.text, tp.text_size )
{
    text.setOrigin( { size.x/2, size.y/2 } );
    text.setPosition( position );
}



// overrides

// object override
void Text::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    return; // do nothing
    // but leave it here b/c maybe do something? idk. future things
}

// Drawable override
void Text::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( text, states );
}
