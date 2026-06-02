#include "../include/StartButton.h"

// constructor
StartButton::StartButton() {
    // bg init
    background.setFillColor( green );
    background.setOutlineColor( black );
    background.setOutlineThickness( outline_thickness );
    background.setOrigin( { background_size.x / 2, background_size.y / 2 } ); // half of its dimensions
    background.setPosition( button_position );

    // text init
    text.setOrigin( { text_size.x / 2, text_size.y / 2 } );
    text.setPosition( button_position );
};

bool StartButton::inBounds( int x, int y ) {
    return bnd.inBounds( x, y );
}



// getters

sf::RectangleShape& StartButton::getBg() {
    return background;
}

sf::Text& StartButton::getText() {
    return text;
}

// drawable

void StartButton::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( background, states );
    target.draw( text, states );
}

void StartButton::onClick( GameState& gs ) {
    gs = start_game;
}