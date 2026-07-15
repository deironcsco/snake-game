#include "../include/Snake.h"
#include "../include/Style.h"

#include <cmath>
#include <iostream>

namespace SnakeParams {

};

Snake::Snake( Window& s_window, GameState& s_gs ) : 
    window( s_window ),
    game_state( s_gs ) {
    // TODO could most of these be passed into as SnakeParams?
    // that may remove the need ot the winodw...no it wouldnt
    // yes it would no it woulnd't i don't want ot pass them in in main
    // vals i need
    int isquare_size{ window.getSquareSize<int>() }; // 50 px
    unsigned int window_size_factor{ window.getWindowGridSize() };
    sf::Vector2f fsquare_vector{ window.getSquareSize<float>(), window.getSquareSize<float>() }; // 50,50
    center_position_game = { // TODO could just be px size/2 +- square size
        (std::ceil((float)window_size_factor/2) * isquare_size) - isquare_size/2, // wsf is 12 300-25 = 275 
        (std::ceil((float)window_size_factor/2) * isquare_size) + isquare_size/2 // 325 (275, 325)
    };
    window_lbound = window.getSquareSize<unsigned int>() / 2;
    window_ubound = window.getWindowSizePx() - (isquare_size /  2);

    // init snake
    snake.push_back(sf::RectangleShape(fsquare_vector)); //add head
    snake[0].setOrigin({fsquare_vector.x/2,fsquare_vector.y/2});
    snake[0].setPosition(center_position_game);
    snake[0].setOutlineColor(Style::black);
    snake[0].setOutlineThickness(Style::outline_thickness);

    // start clock
    clock.start();

    // init direction (to prevent queue::back() seg fault issues)
    direction_queue.push( Direction::UP );

    return;
}

void Snake::handleEvent( std::optional<sf::Event> event, sf::Vector2i mouse_position ) {
    // std::cout << "Snake::handleEvent() start\n";
    if ( event->is<sf::Event::KeyPressed>() ) {
        // std::cout << "Snake::handleEvent() handleDirection start\n";
        handleDirection( event->getIf<sf::Event::KeyPressed>()->code );
        // std::cout << "Snake::handleEvent() handleDirection end\n";
    }
    // std::cout << "Snake::handleEvent() end\n";
    return;
}

void Snake::move() {
    // should also only move if gs is start game
    int isquare_size{ window.getSquareSize<int>() };
    // std::cout << "Snake::move() curr time: " << clock.getElapsedTime().asSeconds() << "\n";
    sf::Time curr{ clock.getElapsedTime() };
    if (curr.asSeconds() >= 0.2) {  //.2
        //dequeueing direction
        if (!direction_queue.empty()) { // TODO does this make sense?
            // std::cout << "\ndir " << direction <<'\n';                    
            if (snake.size() == 1) {
                //dequeue regardless if just one body part
                direction = direction_queue.front();
            }
            else if (direction == Direction::RIGHT && direction_queue.front() != Direction::LEFT ) {
                // std::cout << "right, down\n";
                // std::cout << "head: " << snake[0].getPosition().x << ", " << snake[0].getPosition().y << "\n";
                // std::cout << "head offset: " << snake[0].getPosition().x+isquare_size << ", " << snake[0].getPosition().y+isquare_size << "\n";
                // std::cout << "2nd: " << snake[1].getPosition().x << ", " << snake[1].getPosition().y << "\n"; 
                //only dequeue if second from head is in good spot
                direction = direction_queue.front();
                
            }
            else if (direction == Direction::DOWN && direction_queue.front() != Direction::UP) {
                direction = direction_queue.front();
            }
            else if (direction == Direction::LEFT && direction_queue.front() != Direction::RIGHT) {
                // std::cout << "left, up\n";
                // std::cout << "head: " << snake[0].getPosition().x << ", " << snake[0].getPosition().y << "\n";
                // std::cout << "head offset: " << snake[0].getPosition().x-isquare_size << ", " << snake[0].getPosition().y-isquare_size << "\n";
                // std::cout << "2nd: " << snake[1].getPosition().x << ", " << snake[1].getPosition().y << "\n";
                //^^
                direction = direction_queue.front();
            }
            else if (direction == Direction::UP && direction_queue.front() != Direction::DOWN) {
                direction = direction_queue.front();
            }
            direction_queue.pop(); //pop regardless
        }
        
        //print direction
        // std::cout << "Snake::move() direction: " << static_cast<std::underlying_type<GameState>::type>( direction ) << "\n";
        // print dir queue
        if (!direction_queue.empty()) {
            // std::cout << "Snake::move() dir queue front: " << static_cast<std::underlying_type<GameState>::type>( direction_queue.front() ) << "\n";
            // std::cout << "Snake::move() dir queue size: " << static_cast<std::underlying_type<GameState>::type>( direction_queue.size() ) << "\n";
            // std::cout << "Snake::move() dir queue back: " << static_cast<std::underlying_type<GameState>::type>( direction_queue.back() ) << "\n";
        } else {
            // std::cout << "Snake::move() dir queue: empty!\n";
        }
        
        //move snake and game over testing
        if (direction == Direction::UP) {
            if (snake[0].getPosition().y == window_lbound || 
            isOccupiedBySnake(snake[0].getPosition().x, snake[0].getPosition().y-isquare_size, true)) {
                game_state = GameState::title_screen;
                reInitPosition();
            }
            else {
                MoveSnake(0, -isquare_size);
            }
        }
        else if (direction == Direction::RIGHT) {
            //if head is at edge, or next position is already occupied, game over
            //bounds checking (edge/occupied by other part)
            if (snake[0].getPosition().x == window_ubound || 
            isOccupiedBySnake(snake[0].getPosition().x+isquare_size, snake[0].getPosition().y, true)) {
                game_state = GameState::title_screen;
                reInitPosition();
            }
            else {
                MoveSnake(isquare_size, 0);
            }
        }
        else if (direction == Direction::LEFT) {
            //^^
            if (snake[0].getPosition().x == window_lbound || 
            isOccupiedBySnake(snake[0].getPosition().x-isquare_size, snake[0].getPosition().y, true)) {
                game_state = GameState::title_screen;
                reInitPosition();
            }
            else {
                MoveSnake(-isquare_size, 0);
            }
        }
        else if (direction == Direction::DOWN) {
            //^^
            if (snake[0].getPosition().y == window_ubound || 
            isOccupiedBySnake(snake[0].getPosition().x, snake[0].getPosition().y+isquare_size, true)) {
                game_state = GameState::title_screen;
                reInitPosition();
            }
            else {
                MoveSnake(0, isquare_size);
            }
        }
        
        clock.restart();
    }
    // std::cout << "Snake::move(): end\n";
}

void Snake::handleDirection(sf::Keyboard::Key key) {
    // TOOD replace with move?
    // TODO function to handle direction queue based on the key press? a lot of the code is similar
    //D key
    switch( key ) {
    case sf::Keyboard::Key::D: 
        //if queue is empty you can't queue same or opposite direction
        if (direction_queue.empty() &&
            direction != Direction::RIGHT && direction != Direction::LEFT) {
                direction_queue.push(Direction::RIGHT);
        }
        //can't queue two directions in a row or it's reverse
        else if (direction_queue.back() != Direction::RIGHT &&
            direction_queue.back() != Direction::LEFT) {
                direction_queue.push(Direction::RIGHT);
        }
        break;
    //W key
    case sf::Keyboard::Key::W: {
        //if queue is empty you can't queue same or opposite direction
        if (direction_queue.empty() &&
            direction != Direction::UP && direction != Direction::DOWN) {
                direction_queue.push(Direction::UP);
        }
        //can't queue two directions in a row or it's reverse
        else if (direction_queue.back() != Direction::UP &&
            direction_queue.back() != Direction::DOWN) {
                direction_queue.push(Direction::UP);
        }
        break;
    }
    //A key
    case sf::Keyboard::Key::A: {
        //if queue is empty you can't queue same or opposite direction
        if (direction_queue.empty() &&
            direction != Direction::LEFT && direction != Direction::RIGHT) {
                direction_queue.push(Direction::LEFT);
        }
        //can't queue two directions in a row or it's reverse
        else if (direction_queue.back() != Direction::LEFT &&
                direction_queue.back() != Direction::RIGHT) {
                direction_queue.push(Direction::LEFT);
        }
        break;
    }
    //S key
    case sf::Keyboard::Key::S: {
        //if queue is empty you can't queue same or opposite direction
        if (direction_queue.empty() &&
            direction != Direction::DOWN && direction != Direction::UP) {
                direction_queue.push(Direction::DOWN);
        }
        //can't queue two directions in a row or it's reverse
        else if (direction_queue.back() != Direction::DOWN &&
                direction_queue.back() != Direction::UP) {
                direction_queue.push(Direction::DOWN);
        }
        break;
    }
    }
    return;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for ( int i { 0 }; i < snake.size(); i++ ) {
        target.draw( snake[i], states );
    }
    return;
}

void Snake::reInitPosition() {
    //reinitialize snake, delete all but head
    int size = snake.size(); //if snake.size() in for condition, it's constantly decreasing
    for (int i{ 0 }; i < (size-1); i++) {
        snake.pop_back();
    }
    snake[0].setPosition(center_position_game);

    // reinit direction and direction_queue
    for ( int i { 0 }; i < direction_queue.size(); i++ ) {
        direction_queue.pop();
    }
    direction = Direction::UP;
    direction_queue.push( Direction::UP );
    return;
}



void Snake::play() {
    move();
    return;
}



bool Snake::isOccupiedBySnake(float x, float y, bool exceptFirst) {
    //returns true if inputted x,y coords are occupied by any snake part
    //false otherwise
    //useful for spawning apples and such
    int start{ 0 };
    if (exceptFirst) {
        start = 2;
    }
    for(int i{ start }; i < snake.size(); i++) {
        if (x == snake[i].getPosition().x && y == snake[i].getPosition().y) {
            return true;
        }
    }
    return false;
}

/*
moves snake by offset

inputs
    snake - snake object (vector of rectangles), reference
    x - x offset to new position
    y - y offset to new position
    jgb - just got body part (just ate apple),
            boolean, reference
processes
    loop through snake parts and move them all forward by one grid space
        so that they follow the square ahead of them
    iterates one less if jgb is true, so that last square doesn't permantently...
        ...follow the one it spawned on
outputs
    no return value, but snake will move positions
*/
void Snake::MoveSnake( float x, float y) {
    //initialize
    float prevx{ 0 };
    float prevy{ 0 };
    x += snake[0].getPosition().x; //x position of destination (not offset anymore)
    y += snake[0].getPosition().y; //y position of destination
    int size = snake.size();
    if (just_got_body) { //iterate one less, so last square doesn't move, if just ate apple
        size--;
        just_got_body = false;
    }

    //loop through snake parts
    for (int i{ 0 }; i < size; i++) {
        prevx = snake[i].getPosition().x; //store curr x pos of snake part
        prevy = snake[i].getPosition().y; //^^ for y
        snake[i].setPosition({x,y}); //set snake part to desired position
        x = prevx; //set new desired x position to previous x position
        y = prevy; //^^ for y
    }
    return;
}

GameState Snake::getDrawCondition() {
    return GameState::start_game;
}