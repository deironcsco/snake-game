#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include "Button.h"
#include "Style.h"

// defined in SB.cpp
extern std::unique_ptr<ButtonParams> sb_params;

class StartButton : public Button {
private:
public:
    StartButton();
    void onClick(Control) override;
};


#endif