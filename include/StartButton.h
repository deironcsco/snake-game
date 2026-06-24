#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include "Button.h"
#include "Style.h"

// defined in SB.cpp
extern std::unique_ptr<ButtonParams> sb_params;
// when i remove the extern its a multiple definition thing again

class StartButton : public Button {
private:
public:
    StartButton();
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) override;
};


#endif