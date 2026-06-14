#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include "Button.h"
#include "Style.h"

// defined in SB.cpp
extern std::unique_ptr<ButtonParams> sb_params; // TODO inline? or external?
// when i remove the extern its a multiple definition thing again

class StartButton : public Button {
private:
public:
    StartButton();
    void onClick(Control) override;
};


#endif