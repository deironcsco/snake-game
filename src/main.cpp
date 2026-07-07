#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <queue>

#include "../include/Window.h"
#include "../include/Style.h"
#include "../include/StartButton.h"
#include "../include/GameState.h"
#include "../include/Button.h"
#include "../include/Control.h"
#include "../include/QuitButton.h"
#include "../include/ObjectRegistry.h"
#include "../include/Title.h"
#include "../include/Instructions.h"


void MoveSnake(std::vector<sf::RectangleShape> &snake, float x, float y, bool &jgb);
bool isOccupiedBySnake(std::vector<sf::RectangleShape> snake, float x, float y, bool exceptFirst);


int main() {
    // init window
    unsigned int window_size_factor{ 12 }; // no magic values. e.g. 12x12 grid
    unsigned int window_size_px{ 600 }; // 600px x 600px
    Window window{ window_size_factor, window_size_px };
    
    // init game state
    GameState game_state{ GameState::title_screen };

    // init style
    Style::initStyle( window );

    // global control variable
    Control ctrl = { &game_state, &window };

    // object registry init
    ObjectRegistry obreg{ &ctrl };

    // components
    StartButton sb{ ctrl };
    QuitButton qb{ ctrl };
    Title title{};
    Instructions instructions{};

    // register components to obreg
    obreg.registerObject( &sb );
    obreg.registerObject( &qb );
    obreg.registerObject( &title );
    obreg.registerObject( &instructions );
    









    //snake
    int isquare_size{ window.getSquareSize<int>() };
    sf::Vector2f center_position_game{
        (std::ceil((float)window_size_factor/2) * isquare_size) - isquare_size/2,
        (std::ceil((float)window_size_factor/2) * isquare_size) + isquare_size/2
    };
    std::cout << "center position" << center_position_game.x << ", " << center_position_game.y << "\n";
    sf::Vector2f fsquare_vector{ window.getSquareSize<float>(), window.getSquareSize<float>() };
    std::vector<sf::RectangleShape> snake;
    snake.push_back(sf::RectangleShape(fsquare_vector)); //add head
    snake[0].setOrigin({fsquare_vector.x/2,fsquare_vector.y/2});
    snake[0].setPosition(center_position_game);
    snake[0].setOutlineColor(Style::black);
    snake[0].setOutlineThickness(Style::outline_thickness);

    sf::Clock clock;
    clock.start();
    std::string direction{ "up" };
    std::queue<std::string> direction_queue{};

    //TODO make sure clock and direction events are in there too

    int l_bound{isquare_size / 2};
    unsigned int u_bound{ window_size_px - isquare_size/2 }; // narrowing conversion./ni

    bool just_got_body{ false }; //TODO change to true when eat an apple


    //TODO is there a better way to structure it so handleHover is only covered if it's a hoverable object?
        // object >> hoverable >> button? or something?
    //TODO is it possible to disable mouse during start_game









    while( window.isOpen() ) {
        // event handling
        while( std::optional event = window.pollEvent() ) {
            // get mouse
            sf::Vector2i mouse_position{ sf::Mouse::getPosition( window.getRenderWindow() ) }; 

            // close
            if ( event->is<sf::Event::Closed>() ) {
                window.close();
            }

            // object registry events / hover
            obreg.handleEvent( event, mouse_position );
            obreg.handleHover( mouse_position );

            // test gamestate
            if ( event->is<sf::Event::MouseButtonPressed>() ) {
                std::cout << "gs " << static_cast<std::underlying_type<GameState>::type>( *( ctrl.game_state ) ) << "\n";
            }
















            if (game_state == GameState::title_screen) {
                if ( event->is<sf::Event::MouseButtonPressed>() && sb.inBounds( mouse_position ) ) {
                    std::cout << "SB CLICK\n";
                    //reinitialize snake, delete all but head
                    int size = snake.size(); //if snake.size() in for condition, it's constantly decreasing
                    for (int i{ 0 }; i < (size-1); i++) {
                        snake.pop_back();
                    }
                    snake[0].setPosition(center_position_game);
                    std::cout << "snake position" << snake[0].getPosition().x << ", " << snake[0].getPosition().y << "\n";
                }
            }

            if (game_state == GameState::start_game ) {
                //D key
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) {
                    //if queue is empty you can't queue same or opposite direction
                    if (direction_queue.empty() &&
                        direction != "right" && direction != "left") {
                            direction_queue.push("right");
                    }
                    //can't queue two directions in a row or it's reverse
                    else if (direction_queue.back() != "right" &&
                            direction_queue.back() != "left") {
                            direction_queue.push("right");
                    }
                }
                //W key
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W) {
                    //if queue is empty you can't queue same or opposite direction
                    if (direction_queue.empty() &&
                        direction != "up" && direction != "down") {
                            direction_queue.push("up");
                    }
                    //can't queue two directions in a row or it's reverse
                    else if (direction_queue.back() != "up" &&
                            direction_queue.back() != "down") {
                            direction_queue.push("up");
                    }
                }
                //A key
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A) {
                    //if queue is empty you can't queue same or opposite direction
                    if (direction_queue.empty() &&
                        direction != "left" && direction != "right") {
                            direction_queue.push("left");
                    }
                    //can't queue two directions in a row or it's reverse
                    else if (direction_queue.back() != "left" &&
                            direction_queue.back() != "right") {
                            direction_queue.push("left");
                    }
                }
                //S key
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S) {
                    //if queue is empty you can't queue same or opposite direction
                    if (direction_queue.empty() &&
                        direction != "down" && direction != "up") {
                            direction_queue.push("down");
                    }
                    //can't queue two directions in a row or it's reverse
                    else if (direction_queue.back() != "down" &&
                            direction_queue.back() != "up") {
                            direction_queue.push("down");
                    }
                }
            }
        }
















        if ( game_state == GameState::start_game ) {
            
            //move snake
            sf::Time curr{ clock.getElapsedTime() };
            if (curr.asSeconds() >= 0.3) {  //.2

                // std::cout << "D: " << direction << "\n";
                if (direction_queue.size() != 0) {
                    // std::cout << "DQ...f: " << direction_queue.front() << ", s: " << direction_queue.size();
                }
                else {
                    // std::cout << "DQ...empty\n";
                }
                //dequeueing direction
                if (!direction_queue.empty()) {
                    // std::cout << "\ndir " << direction <<'\n';                    
                    if (snake.size() == 1) {
                        //dequeue regardless if just one body part
                        direction = direction_queue.front();
                    }
                    else if (direction == "right" && direction_queue.front() != "left" ) {
                        // std::cout << "right, down\n";
                        // std::cout << "head: " << snake[0].getPosition().x << ", " << snake[0].getPosition().y << "\n";
                        // std::cout << "head offset: " << snake[0].getPosition().x+isquare_size << ", " << snake[0].getPosition().y+isquare_size << "\n";
                        // std::cout << "2nd: " << snake[1].getPosition().x << ", " << snake[1].getPosition().y << "\n"; 
                        //only dequeue if second from head is in good spot
                        direction = direction_queue.front();
                        
                    }
                    else if (direction == "down" && direction_queue.front() != "up") {
                        direction = direction_queue.front();
                    }
                    else if (direction == "left" && direction_queue.front() != "right") {
                        // std::cout << "left, up\n";
                        // std::cout << "head: " << snake[0].getPosition().x << ", " << snake[0].getPosition().y << "\n";
                        // std::cout << "head offset: " << snake[0].getPosition().x-isquare_size << ", " << snake[0].getPosition().y-isquare_size << "\n";
                        // std::cout << "2nd: " << snake[1].getPosition().x << ", " << snake[1].getPosition().y << "\n";
                        //^^
                        direction = direction_queue.front();
                    }
                    else if (direction == "up" && direction_queue.front() != "down") {
                        direction = direction_queue.front();
                    }
                    direction_queue.pop(); //pop regardless
                }
                
                //move snake and game over testing
                if (direction == "up") {
                    if (snake[0].getPosition().y == l_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x, snake[0].getPosition().y-isquare_size, true)) {
                        game_state = GameState::title_screen;
                    }
                    else {
                        MoveSnake(snake, 0, -isquare_size, just_got_body);
                    }
                }
                else if (direction == "right") {
                    //if head is at edge, or next position is already occupied, game over
                    //bounds checking (edge/occupied by other part)
                    if (snake[0].getPosition().x == u_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x+isquare_size, snake[0].getPosition().y, true)) {
                        game_state = GameState::title_screen;
                    }
                    else {
                        MoveSnake(snake, isquare_size, 0, just_got_body);
                    }
                }
                else if (direction == "left") {
                    //^^
                    if (snake[0].getPosition().x == l_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x-isquare_size, snake[0].getPosition().y, true)) {
                        game_state = GameState::title_screen;
                    }
                    else {
                        MoveSnake(snake, -isquare_size, 0, just_got_body);
                    }
                }
                else if (direction == "down") {
                    //^^
                    if (snake[0].getPosition().y == u_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x, snake[0].getPosition().y+isquare_size, true)) {
                        game_state = GameState::title_screen;
                    }
                    else {
                        MoveSnake(snake, 0, isquare_size, just_got_body);
                    }
                }
                
                clock.restart();
            }
        }












        // display
        // TODO overide draw command? and the other three, just do drawOR or drawObReg or something for the current display
        // window.display( obreg );
        window.getRenderWindow().clear();
        if (game_state == GameState::start_game) {
            for (int i{ 0 }; i < snake.size(); i++) {
                window.getRenderWindow().draw(snake[i]);
            }   
        }
        window.getRenderWindow().draw(obreg);
        window.getRenderWindow().display();
    }
    return 0;
}












void MoveSnake(std::vector<sf::RectangleShape> &snake, float x, float y, bool &jgb) {
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

    //initialize
    float prevx{ 0 };
    float prevy{ 0 };
    x += snake[0].getPosition().x; //x position of destination (not offset anymore)
    y += snake[0].getPosition().y; //y position of destination
    int size = snake.size();
    if (jgb) { //iterate one less, so last square doesn't move, if just ate apple
        size--;
        jgb = false;
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

bool isOccupiedBySnake(std::vector<sf::RectangleShape> snake, float x, float y, bool exceptFirst) {
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