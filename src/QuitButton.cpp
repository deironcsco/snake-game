#include "../include/QuitButton.h"

// params
namespace QB {
    // no magic values
    sf::Vector2f bg_size{ 100, 75 };
    sf::Vector2f text_size { 70, 35 };

    // params pointer
    std::unique_ptr<ButtonParams> params = std::make_unique<ButtonParams>(ButtonParams {
        bg_size,
        text_size,
        Style::normal_text_size,
        "QUIT",
        Style::font,
        Style::low_button_position,
        Style::red,
        Style::black,
        Style::outline_thickness,
    });
}

// constructor
QuitButton::QuitButton(Control& s_ctrl) : Button( *QB::params, &s_ctrl ) {};

// close window on quit
void QuitButton::onClick() {
    ctrl->window->close();
}