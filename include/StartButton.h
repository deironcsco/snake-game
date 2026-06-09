#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include "Button.h"
#include "Style.h"

class StartButton : public Button {
private:
public:
    StartButton( ButtonParams* );
    void onClick( Control ) override;
};


#endif