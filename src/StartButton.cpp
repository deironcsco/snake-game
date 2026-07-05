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
    Style::normal_text_size,
    sb_text,
    Style::font,
    Style::button_position,
    Style::green,
    Style::black,
    Style::outline_thickness,
} );

StartButton::StartButton(Control* s_ctrl) : Button( sb_params.get(), s_ctrl) {}

void StartButton::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    if ( event->is<sf::Event::MouseButtonPressed>() && inBounds( mouse_position ) ) {
        *(ctrl->game_state) = start_game;
    }
}
