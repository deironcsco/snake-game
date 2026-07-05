#ifndef CONTROL_H
#define CONTROL_H

#include "GameState.h"
#include "Window.h"

// Control bundles important info that originally I needed for
// virtual functions like onClick that couldn't have different 
// parameters 

struct Control {
    GameState* game_state;
    Window* window;
};
// they need to be pointers and not references b/c they should be nullable


#endif