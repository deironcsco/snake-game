#include "../include/StartButtonNew.h"

StartButton::StartButton( ButtonParams* bp ) : Button( bp ) {}

void StartButton::onClick( Control ctrl ) {
    ctrl.gs = start_game;
}