#include "../include/Snake.h"

namespace SnakeParams {

};

Snake::Snake(unsigned int s_window_ubound, unsigned int s_window_lbound) : window_ubound(s_window_ubound), window_lbound(s_window_lbound) {
    return;
}

void Snake::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    return;
}

void Snake::move(Direction) {
    return;
}

void Snake::handleDirection(std::optional<sf::Event>) {
    return;
}

void Snake::draw(sf::RenderTarget&, sf::RenderStates) const {
    return;
}

void Snake::reInitPosition() {
    return;
}

void Snake::play() {
    return;
}

bool Snake::isOccupiedBySnake() {
    return;
}