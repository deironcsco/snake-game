#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <queue>

#include "Object.h"
#include "Window.h"

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class Snake : public Object {
private:
    Direction direction{ Direction::UP };
    std::vector<sf::RectangleShape> snake;
    Window& window;
    unsigned int window_ubound;
    unsigned int window_lbound; // TODO - combine these into a struct?
    sf::Clock clock;
    std::queue<Direction> direction_queue{};
    bool just_got_body{ false };
    GameState& game_state;
    sf::Vector2f center_position_game;
public:
    Snake(Window&, GameState&);
    void handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) override;
    void move();
    void handleDirection(sf::Keyboard::Key);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void reInitPosition();
    void play() override;
    bool isOccupiedBySnake(float x, float y, bool exceptFirst);
    void MoveSnake(float x, float y);
    GameState getDrawCondition() override;
};

#endif
