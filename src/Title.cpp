#include "../include/Title.h"
#include "../include/Style.h"

namespace TitleP {
    // no magic values
    sf::Vector2f position{ 300, 200 };
    sf::Vector2f size{ 134, 50 };
    unsigned int text_size{ 50 };

    // title params
    TextParams tp { 
        position,
        text_size,
        size,
        Style::font,
        "Snake"
    };
}



// constructor
Title::Title() : Text( TitleP::tp ) {}



// overrides

bool Title::handleHover( sf::Vector2i mouse_position ) {
    return false; // do nothing
}

GameState Title::getDrawCondition() {
    return GameState::title_screen;
}
