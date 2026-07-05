#ifndef CONTROL_H
#define CONTROL_H

#include "GameState.h"
#include "Window.h"

// Control is because idk how to make whatever argument list you want for
// ...virtual function onClick (now handleEvent), so we just putting all game info here so 
// ...if the buttons need it they can have it all as one struct. yeah?
struct Control {
    GameState* game_state;
    Window* window;
};
// they need to be pointers and not references b/c they have to be nullable


#endif