#include <memory>

#include "../include/StartButton.h"

// SB params
namespace SB {
    // no magic values
    sf::Vector2f bg_size{ 150, 100 };
    sf::Vector2f text_size{ 80, 30 };
    sf::String text{ "START" };

    // params pointer
    std::unique_ptr<ButtonParams> params = std::make_unique<ButtonParams>( ButtonParams{
        bg_size,
        text_size,
        Style::normal_text_size,
        text,
        Style::font,
        Style::button_position,
        Style::green, 
        Style::black,
        Style::outline_thickness,
    } );
}

// constructor
StartButton::StartButton( Control& s_ctrl ) : Button( *SB::params, &s_ctrl) {}

// change game state on click
void StartButton::onClick() {
    *( ctrl->game_state ) = GameState::start_game;
}
