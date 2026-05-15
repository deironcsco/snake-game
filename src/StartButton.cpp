#include "../include/StartButton.h"

StartButton::StartButton() {
    // bg 
    bg.setFillColor( green );
    bg.setOutlineColor( black );
    bg.setOutlineThickness( outline_thickness );
    bg.setOrigin( { bg_v.x / 2, bg_v.y / 2 } ); // half of its dimensions
    bg.setPosition( button_position );

    // text
    text.setOrigin( { text_v.x / 2, text_v.y / 2 } );
    text.setPosition( button_position );

};

bool StartButton::inBounds( int x, int y ) {
    return bnd.inBounds( x, y );
}

sf::RectangleShape& StartButton::getBg() {
    return bg;
}

sf::Text& StartButton::getText() {
    return text;
}