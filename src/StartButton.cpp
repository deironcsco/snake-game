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
    &g_ctrl
} );

StartButton::StartButton() : Button( sb_params.get() ) {}

// void StartButton::onClick( Control ctrl ) {
//     *(ctrl.gs) = start_game;
// }

void StartButton::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    if ( inBounds( mouse_position ) ) {
        *(ctrl->gs) = start_game;
    }
}
