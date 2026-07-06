#include "../include/Instructions.h"
#include "../include/Style.h"

namespace InstructionsParams {
    sf::Vector2f position{ 300, 300 };
    unsigned int text_size{ 20 };
    sf::Vector2f size{ 136, 25 };
    sf::String text{ "WASD to Move" };

    TextParams params {
        position,
        text_size,
        size,
        Style::font,
        text
    };
}



// constructor

Instructions::Instructions() : Text( InstructionsParams::params ) {}



// overrides

bool Instructions::handleHover( sf::Vector2i mouse_position ) {
    return false; // do nothing
}

GameState Instructions::getDrawCondition() {
    return GameState::title_screen;
}