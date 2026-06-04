#ifndef STARTBUTTONNEW_H
#define STARTBUTTONNEW_H
//TODO rename this to startbutton

#include "Button.h"
#include "Style.h"

class StartButton : public Button {
private:
public:
    StartButton( ButtonParams );
    void onClick( Control ) override;
};


#endif