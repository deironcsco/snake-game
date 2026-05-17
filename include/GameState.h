#ifndef GAMESTATE_H
#define GAMESTATE_H

// flag indicating where we are in the game
// e.g. are you in the title screen, or are you playing, etc.

enum GameState {
    title_screen, // before game start
    start_game // game started
};

#endif