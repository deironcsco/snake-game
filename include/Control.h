#ifndef CONTROL_H
#define CONTROL_H

#include "GameState.h"
#include "Window.h"

// Control is because idk how to make whatever argument list you want for
// ...virtual function onClick, so we just putting all game info here so 
// ...if the buttons need it they can have it all as one struct. yeah?
struct Control {
    GameState* gs;
    Window* w;
};

// TODO - make this a pointer?
// global instance of control, defined in main
inline Control g_ctrl{ nullptr, nullptr };

#endif