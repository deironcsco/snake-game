#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <queue>

#include "Object.h"

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class Snake : public Object {
private:
    Direction dir;
    std::vector<sf::RectangleShape> snake;
    unsigned int window_ubound;
    unsigned int window_lbound; // TODO - combine these into a struct?
    sf::Clock clock;
    std::queue<Direction> dir_queue;
public:
    Snake(unsigned int, unsigned int);
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) override;
    void move(Direction);
    void handleDirection(std::optional<sf::Event>);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void reInitPosition();
    void play();
    bool isOccupiedBySnake();
};

#endif
