#include "../include/StartButton.h"

#include <memory>

// no magic values
namespace SB {
    // gonna copy paste this todo from SB private member vars. i'm not really satisifed with where this should go

    // TODO - idk if it feels right to have the params here, b/c i don't need them for anything besides the constructor
    // having them outside though feels also a bit unnecessary b/c they don't need to be global? but i think that's a weak argument
    // i could namespce them globally. 
    // it's just that if someone took teh startbutton, i don't want to confuse them with all this stuf ehre
    // changing bg size doesn't actually do anything in the SB, b/c it was set when it was constructed
    // i think the namespaced params are a bit better. perhaps

    sf::Vector2f bg_size{ 150, 100 };
    sf::Vector2f text_size{ 80, 30 };
    sf::String text{ "START" };

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

StartButton::StartButton(Control* s_ctrl) : Button( SB::params.get(), s_ctrl) {}

void StartButton::onClick() {
    *(ctrl->game_state) = GameState::start_game;
}
