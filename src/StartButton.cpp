#include "../include/StartButton.h"

StartButton::StartButton() {
    // bg 
    bg.setFillColor( green );
    bg.setOutlineColor( black );
    bg.setOutlineThickness( outline_thickness );
    bg.setOrigin( { bg_x / 2, bg_y / 2 } ); // half of its dimensions
    bg.setPosition( button_position );

    // text
    text.setOrigin( { text_x / 2, text_y / 2 } );
    text.setPosition( button_position );

    // boundaries
    // origin +- half of size
    x_lbound = button_position.x - bg_x / 2; 
    x_ubound = button_position.x + bg_x / 2;
    y_lbound = button_position.y - bg_y / 2;
    y_ubound = button_position.y + bg_y / 2;
};

bool StartButton::inBounds(int x, int y) {
    return x < x_ubound && 
           x > x_lbound && 
           y < y_ubound && 
           y > y_lbound;
}

sf::RectangleShape& StartButton::getBg() {
    return bg;
}

sf::Text& StartButton::getText() {
    return text;
}