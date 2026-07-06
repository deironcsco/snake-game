#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "Text.h"

class Instructions : public Text {
private:
public:
    Instructions(); // constructor

    // overrides
    bool handleHover( sf::Vector2i mouse_position ) override;
    GameState getDrawCondition() override;
};

#endif