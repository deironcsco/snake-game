#include "Button.h"

// constructor
Button::Button( ButtonParams* bp ) : 
    background_size( bp->background_size ),
    background( bp->background_size ),
    text_size( bp->text_size ),
    text( bp->font, bp->text, bp->font_size ),
    bnd( {
        bp->position.x + bp->background_size.x / 2,
        bp->position.x - bp->background_size.x / 2,
        bp->position.y + bp->background_size.y / 2,
        bp->position.y - bp->background_size.y / 2,
    } ),
    ctrl( bp->ctrl )
{
    // bg init
    background.setFillColor( bp->background_color );
    background.setOutlineColor( bp->outline_color );
    background.setOutlineThickness( bp->outline_thickness );
    background.setOrigin( { bp->background_size.x / 2, bp->background_size.y / 2 } ); // half of its dimensions
    background.setPosition( bp->position );

    // text init
    text.setOrigin( { bp->text_size.x / 2, bp->text_size.y / 2 } );
    text.setPosition( bp->position );
};




// getters

sf::RectangleShape& Button::getBg() {
    return background;
}

sf::Text& Button::getText() {
    return text;
}



// drawable

void Button::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( background, states );
    target.draw( text, states );
}

bool Button::inBounds( sf::Vector2i mouse_position ) {
    return bnd.inBounds( mouse_position.x, mouse_position.y );
}

bool Button::handleHover(sf::Vector2i mouse_position) {
    if ( inBounds( mouse_position ) ) { // this->?
        ctrl->window->setCursorHand( ctrl->window->getWindow() );
        return true;
    }
    return false;
}

GameState Button::getDrawCondition() {
    return GameState{ title_screen };
}




