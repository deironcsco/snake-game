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
    StartButton(Control*);
    void onClick() override;
};


#endif