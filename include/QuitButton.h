#ifndef QUITBUTTON_H
#define QUITBUTTON_H

#include "Button.h"
#include "Style.h"

extern std::unique_ptr<ButtonParams> qb_params;
// when i remove the extern its a multiple definition thing again
// yeah cause it's defined multiple times dummy. here and in QB.cpp

class QuitButton : public Button {
private:
public:
    QuitButton(Control*);
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) override;
};

#endif