#ifndef QUITBUTTON_H
#define QUITBUTTON_H

#include "Button.h"
#include "Style.h"

// extern std::unique_ptr<ButtonParams> qb_params;
// when i remove the extern its a multiple definition thing again
// yeah cause it's defined multiple times dummy. here and in QB.cpp
// defined here b/c why?

// QuitButton component, for quitting the game on open

class QuitButton : public Button {
private:
public:
    QuitButton( Control& ); // constructor
    void onClick() override; // Button override
};

#endif