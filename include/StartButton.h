#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include "Button.h"
#include "Style.h"

// StartButton component starts the game

class StartButton : public Button {
private:
public:
    StartButton( Control& ); // constructor
    void onClick() override; // Button override
};


#endif