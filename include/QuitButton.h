#ifndef QUITBUTTON_H
#define QUITBUTTON_H

#include "Button.h"
#include "Style.h"

extern std::unique_ptr<ButtonParams> qb_params; // TODO inline? or external?
// when i remove the extern its a multiple definition thing again

class QuitButton : public Button {
private:
public:
    QuitButton();
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) override;
};

#endif