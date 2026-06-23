#include "../include/QuitButton.h"

sf::Vector2f qb_bg_size{ 100, 75 }; // TODO this is global scope and can conflict. should probably namespace components?
sf::Vector2f qb_text_size { 70, 35 };
std::unique_ptr<ButtonParams> qb_params = std::make_unique<ButtonParams>(ButtonParams {
    qb_bg_size,
    qb_text_size,
    normal_text_size,
    "QUIT",
    font,
    low_button_position,
    red,
    black,
    outline_thickness,
    &g_ctrl
});

QuitButton::QuitButton() : Button( qb_params.get() ) {};

void QuitButton::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    if ( event->is<sf::Event::MouseButtonPressed>() && inBounds( mouse_position ) ) {
        ctrl->window->getWindow().close();
    }
}