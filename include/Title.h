#ifndef TITLE_H
#define TITLE_H

#include "Text.h"

// Title is the title text on the front

class Title : public Text {
private:
public:
    Title(); // constructor

    // overrides
    bool handleHover( sf::Vector2i mouse_position ) override;
    GameState getDrawCondition() override;
};

#endif
