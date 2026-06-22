#include "../include/StartButton.h"

#include <memory>

// no magic values
sf::Vector2f sb_bg_size{ 150, 100 };
sf::Vector2f sb_text_size{ 80, 30 };
sf::String sb_text{ "START" };

// init params here so i don't have to do them in main
std::unique_ptr<ButtonParams> sb_params = std::make_unique<ButtonParams>( ButtonParams{
    sb_bg_size,
    sb_text_size,
    normal_text_size,
    sb_text,
    font,
    button_position,
    green,
    black,
    outline_thickness,
    &g_ctrl // TODO should this be a pointer? or does it not matter...
} );

StartButton::StartButton() : Button( sb_params.get() ) {}

// void StartButton::onClick( Control ctrl ) {
//     *(ctrl.gs) = start_game;
// }

// TODO so button should have the mouse button pressed and inbounds by default, then it should call startbutton::handleevent?
    // is that even possible?
    // either way i think button should handle the mouse button pressed and all that, yeah?
    // yeah like another pure virtual func onClick. i feel like that makes more sense
void StartButton::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    if ( event->is<sf::Event::MouseButtonPressed>() && inBounds( mouse_position ) ) {
        *(ctrl->gs) = start_game;
    }
}
