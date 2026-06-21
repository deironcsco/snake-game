#include "../include/QuitButton.h"
// #include "../include/Style.h"

// struct ButtonParams {
// public:
//     sf::Vector2f background_size;
//     sf::Vector2f text_size;
//     unsigned int font_size;
//     sf::String text;
//     sf::Font font;
//     sf::Vector2f position;
//     sf::Color background_color;
//     sf::Color outline_color;
//     float outline_thickness;
//     Control ctrl; // TODO reference to a control?
// };

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

// void QuitButton::onClick( Control ctrl ) {
//     ctrl.w->getWindow().close(); // does this work
// }

void QuitButton::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    ctrl->w->getWindow().close();
}