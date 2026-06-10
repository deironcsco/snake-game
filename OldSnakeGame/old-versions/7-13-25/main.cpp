#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void MoveSnake(std::vector<sf::RectangleShape>&, float, float, bool&); //moves the whole snake by offset
bool isOccupiedBySnake(std::vector<sf::RectangleShape>, float, float, bool=false); //is (x,y) occupied by a snake square?
int randomTile();

int main() {
    
    //simple and fast multimedia library
    
    std::srand(std::time(0)); //seed random

    //info
    //colors
    sf::Color black{ 0, 0, 0 };
    sf::Color red{ 200, 0, 0 };
    sf::Color green{ 30, 170, 0 };
    //font
    const sf::Font font("CaviarDreams.ttf");
    //text sizes
    unsigned int titletext_size{ 50 }; //for any text that's bigger
    unsigned int normaltext_size{ 30 }; //sf::text constructor expecting uint. this just to stop the warning
    //positions
    sf::Vector2f title_position{ 300, 200 };
    sf::Vector2f button_position{ 300, 400 };
    sf::Vector2f center_position{ 300, 300 };

    //misc
    float outline_thickness{ -5 }; //outline thickness of shapes
    unsigned int usquare_size{ 50 }; //size of individual square in grid, unsigned int for vectors sizes
    int isquare_size{ (int)usquare_size }; //int of usquare_size, for utilizing in game and stuff (e.g. moving one square size forward/backwards)
    sf::Vector2u usquare_vector{ usquare_size, usquare_size }; //a vector of square size, unsigned int for creating window
    sf::Vector2f fsquare_vector{ usquare_vector }; //^^, float for creating shapes
    unsigned int windowsize_factor { 12 }; //basically dims of window (in this case, 12x12 of squares)
    int l_bound{ 0 }; //lower bound of map
    int u_bound{ 550 }; //upperbound bound of map
    int win_condition{ 100 }; //size of snake needed to win

    //game control vars
    bool just_got_body{ false }; //just ate apple (for move function, doesn't move first time)
    bool start_game{ false }; //for starting the game
    bool cursor_is_arrow{ true }; //for cursor being arrow
    bool game_over{ false }; //if game over or not
    bool win_game{ false }; //did you win the game

    //window
    sf::RenderWindow window(sf::VideoMode(windowsize_factor * usquare_vector), "Snake");
    //disable manipulating window size (cuz it fucks with graphics)
    const std::optional<sf::Vector2u> window_size{windowsize_factor * usquare_vector};
    window.setMinimumSize(window_size);
    window.setMaximumSize(window_size);

    //snake
    std::vector<sf::RectangleShape> snake;
    snake.push_back(sf::RectangleShape(fsquare_vector)); //add head
    snake[0].setPosition(center_position);
    snake[0].setOutlineColor(black);
    snake[0].setOutlineThickness(outline_thickness);

    //apple
    sf::RectangleShape apple{ fsquare_vector };
    float apple_x = randomTile();
    float apple_y = randomTile();
    while (apple_x == center_position.x && apple_y == center_position.y) { //while on the snake position
        apple_x = randomTile();
        apple_y = randomTile();
    }
    apple.setPosition({apple_x, apple_y});
    apple.setOutlineColor(black);
    apple.setOutlineThickness(outline_thickness);
    apple.setFillColor(red);

    //TITLE SCREEN
    //title text
    float title_x{ 134 };
    float title_y{ 50 };
    sf::Text title(font, "Snake", titletext_size); //before you start
    title.setOrigin({title_x/2, title_y/2});
    title.setPosition(title_position);
    //start button bg
    float startbutton_bgx{ 150 };
    float startbutton_bgy{ 100 };
    sf::RectangleShape startbutton_bg({startbutton_bgx, startbutton_bgy});
    startbutton_bg.setFillColor(green);
    startbutton_bg.setOutlineColor(black);
    startbutton_bg.setOutlineThickness(outline_thickness);
    startbutton_bg.setOrigin({startbutton_bgx/2, startbutton_bgy/2}); //half of its dimensions
    startbutton_bg.setPosition(button_position);
    //start button text
    float startbutton_textx{ 80 };
    float startbutton_texty{ 30 };
    sf::Text startbutton_text(font, "START", normaltext_size);
    startbutton_text.setOrigin({startbutton_textx/2, startbutton_texty/2});
    startbutton_text.setPosition(button_position);
    //start button boundaries
    float startbuttonx_lbound{ button_position.x - startbutton_bgx/2 }; //origin +- half of size
    float startbuttonx_ubound{ button_position.x + startbutton_bgx/2 };
    float startbuttony_lbound{ button_position.y - startbutton_bgy/2 };
    float startbuttony_ubound{ button_position.y + startbutton_bgy/2 };
    //instructions
    float instructions_x{ 136 };
    float instructions_y{ 25 };
    sf::Text instructions{ font, "WASD to Move", 20 };
    instructions.setOrigin({instructions_x/2, instructions_y/2});
    instructions.setPosition(center_position);

    //GAME OVER SCREEN
    //game over text
    float gameover_textx{ 280 }; //x dim of gameover text
    float gameover_texty{ 55 }; //y dim ^^
    sf::Text gameover_text{font, "Game Over!", titletext_size};
    gameover_text.setOrigin({gameover_textx/2, gameover_texty/2});
    gameover_text.setPosition(title_position);
    //play again button bg
    float playagain_bgx{ 200 };
    float playagain_bgy{ 75 };
    sf::RectangleShape playagain_bg{ startbutton_bg }; //use startbutton bg as a start 
    playagain_bg.setSize({playagain_bgx, playagain_bgy});
    playagain_bg.setOrigin({playagain_bgx/2, playagain_bgy/2});
    //play again text
    float playagain_textx{ 165 }; //setOrigin() expects floats
    float playagain_texty{ 30 };
    sf::Text playagain_text{font, "PLAY AGAIN", normaltext_size};
    playagain_text.setOrigin({playagain_textx/2, playagain_texty/2});
    playagain_text.setPosition(button_position);
    //play again button boundaries
    float playagainx_lbound{ button_position.x - playagain_bgx/2 }; //bg position +- x/2
    float playagainx_ubound{ button_position.x + playagain_bgx/2 };
    float playagainy_lbound{ button_position.y - playagain_bgy/2 };
    float playagainy_ubound{ button_position.y + playagain_bgy/2 };
    //quit button bg
    sf::Vector2f quitbutton_position{300, 500}; //button position
    float quitbutton_bgx{ 100 };
    float quitbutton_bgy{ 75 };
    sf::RectangleShape quitbutton_bg{{quitbutton_bgx, quitbutton_bgy}};
    quitbutton_bg.setFillColor(red);
    quitbutton_bg.setOutlineColor(black);
    quitbutton_bg.setOutlineThickness(outline_thickness);
    quitbutton_bg.setOrigin({quitbutton_bgx/2, quitbutton_bgy/2});
    quitbutton_bg.setPosition({quitbutton_position.x, quitbutton_position.y});
    //quit button text
    float quitbutton_textx{ 70 };
    float quitbutton_texty{ 35 };
    sf::Text quitbutton_text{ font, "QUIT", normaltext_size };
    quitbutton_text.setOrigin({quitbutton_textx/2, quitbutton_texty/2});
    quitbutton_text.setPosition({quitbutton_position.x, quitbutton_position.y});
    //quit button boundaries
    float quitbuttonx_lbound{quitbutton_position.x - quitbutton_bgx/2};
    float quitbuttonx_ubound{quitbutton_position.x + quitbutton_bgx/2};
    float quitbuttony_lbound{quitbutton_position.y - quitbutton_bgy/2};
    float quitbuttony_ubound{quitbutton_position.y + quitbutton_bgy/2};

    //WIN SCREEN
    //win screen text
    sf::Vector2f wintext_size{200, 60}; //FIRST FUCKING TRY HAHAHAHA (at guessing the size)
    sf::Text win_text{font, "You Win!", titletext_size};
    win_text.setOrigin({wintext_size.x/2, wintext_size.y/2});
    win_text.setPosition(center_position);

    //win screen height is 60
    //center pos is 300
    //top of win text is 330
    //title is 200
    //tallest is 248
    //so 200+124 is  324
    //that math is not mathing
    //B overlapped at 198
    //so that means the y bounds of B should be about 100,300
    //oh yeah you subtract 30
    //so top of win text is 270
    //and tallest is 124, so ot goes down to 324
    //so it needs to add 324-270 = 54 units
    //which would make the top 200-54-124 = 200-178 = 22
    //so add another 11 units or something
    //so add 54+11 = 65 units
    //might be uneven. we can have a vector of sizes if you want
    //for each of the sizes of the sprites

   

    //start clock
    sf::Clock clock;
    clock.start();
    std::string direction{ "up" };

    //textures
    std::vector<sf::Texture> textures{sf::Texture{"pics\\A.jpeg"},
                                    sf::Texture{"pics\\B.PNG"},
                                    sf::Texture{"pics\\bucket.jpeg"},
                                    sf::Texture{"pics\\D.jpeg"},
                                    sf::Texture{"pics\\E.jpeg"},
                                    sf::Texture{"pics\\E.png"},
                                    sf::Texture{"pics\\E.jpeg"},
                                    sf::Texture{"pics\\F.png"},
                                    sf::Texture{"pics\\J.jpg"},
                                    sf::Texture{"pics\\K.png"},
                                    sf::Texture{"pics\\K.png"},
                                    sf::Texture{"pics\\L.jpeg"},
                                    sf::Texture{"pics\\M.jpeg"},
                                    sf::Texture{"pics\\R.png"},
                                    sf::Texture{"pics\\S.png"},
                                    sf::Texture{"pics\\Z.JPG"},};

    std::vector<sf::Vector2f> sprite_sizes {{150,200}, //A
                                            {150,198}, //B
                                            {200,124}, //bucket
                                            {150,200}, //D
                                            {150,200}, //E
                                            {150,200}, //E
                                            {150,200}, //E
                                            {150,244}, //F
                                            {180,164}, //J
                                            {150,200}, //K
                                            {150,200}, //K
                                            {150,200}, //L
                                            {150,200}, //M
                                            {150,248}, //R
                                            {150,200}, //S
                                            {200,149} //Z
                                        };
    
    //initialize sprites vector
    int counter{ 0 };
    std::vector<sf::Sprite> sprites;
    sf::Vector2f sprite_pos_difference{0,54+11}; //see scratch work at line 163ish (its so it don't overlap with the win text (and is somewhat centered))
    for (int i{ 0 }; i < textures.size(); i++) {
        sprites.push_back(sf::Sprite(textures[i]));
        sprites[i].setPosition(title_position - sprite_pos_difference);
        sprites[i].setOrigin({sprite_sizes[i].x/2, sprite_sizes[i].y/2});
    }

    int num_sprites{ 16 };
    int curr_sprite { std::rand() % num_sprites };

    bool just_changed_direction { false };
    
    //open window
    while(window.isOpen()) {
        //event loop
        while (std::optional event = window.pollEvent()) {
            //close
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            //for testing
            //get mouse position
            /*
            if (event->is<sf::Event::MouseButtonPressed>()) {
                std::cout << event->getIf<sf::Event::MouseButtonPressed>()->position.x << ", " << event->getIf<sf::Event::MouseButtonPressed>()->position.y << "\n";
            } 
            */

            //title screen
            if (!start_game && !game_over) { 
                //button functionality to start button
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (sf::Mouse::getPosition(window).x < startbuttonx_ubound && 
                    sf::Mouse::getPosition(window).x > startbuttonx_lbound && 
                    sf::Mouse::getPosition(window).y < startbuttony_ubound && 
                    sf::Mouse::getPosition(window).y > startbuttony_lbound) {
                        start_game = true;
                    }
                }
                
                /*
                //testing pics of people
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) {
                    counter++;
                    std::cout << counter <<  " " << sprites[counter].getScale().x << ", " << sprites[counter].getScale().y << "\n";
                    std::cout << counter << " " << sprites[counter].getRotation().asDegrees() << "\n";
                    window.clear();
                    //window.draw(sprites[counter]);
                    window.display();
                }
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A) {
                    counter--;
                    std::cout << counter <<  " " << sprites[counter].getScale().x << ", " << sprites[counter].getScale().y << "\n";
                    window.clear();
                    //window.draw(sprites[counter]);
                    window.display();
                }*/
                
                //cursor change if hover
                if (sf::Mouse::getPosition(window).x < startbuttonx_ubound && 
                sf::Mouse::getPosition(window).x > startbuttonx_lbound && 
                sf::Mouse::getPosition(window).y < startbuttony_ubound && 
                sf::Mouse::getPosition(window).y > startbuttony_lbound) {
                    const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value(); //.value() because optional. have to make a cursor before passing to window
                    window.setMouseCursor(cursor);
                    cursor_is_arrow = false;
                }
                //cursor back to normal if not hovering
                else if (!cursor_is_arrow) {
                    const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value(); //.value() because optional. have to make a cursor before passing to window
                    window.setMouseCursor(cursor);
                    cursor_is_arrow = true;
                }
            }
            //normal play
            if (start_game && !game_over && !win_game) { 
                //make sure cursor is arrow
                if (!cursor_is_arrow) {
                    const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value(); //.value() because optional. have to make a cursor before passing to window
                    window.setMouseCursor(cursor);
                    cursor_is_arrow = true;
                }

                //movement and bounds checking
                //D key
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::D) {
                    //std::cout << (snake[0].getPosition().x == u_bound) << "\n";
                    if (direction != "right") {
                        sf::Time curr { clock.getElapsedTime() };
                        std::cout << "sec: " << curr.asSeconds() << "d: " << direction << "\n";
                        if (curr.asSeconds() > 0.05) {
                            just_changed_direction = true;
                            //std::cout << "sec: " << curr.asSeconds();
                            clock.restart();
                        }
                    }
                    //only go right if there isn't a body part to the right (otherwise do nothing)
                    if (snake.size() >= 2 && (snake[1].getPosition().x != snake[0].getPosition().x+isquare_size)){
                        direction = "right";
                    }
                    //above condition doesn't apply when size is 1
                    else if (snake.size() == 1) {
                        direction = "right";
                    }
                    //std::cout << direction << "\n";
                    //just_changed_direction = true;

                }
                //W key
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::W) {
                    if (direction != "up") {
                        sf::Time curr { clock.getElapsedTime() };
                        std::cout << "sec: " << curr.asSeconds() << "d: " << direction << "\n";
                        if (curr.asSeconds() > 0.05) {
                            just_changed_direction = true;   
                            //std::cout << "sec: " << curr.asSeconds();
                            clock.restart();
                        }
                    }
                    if (snake.size() >= 2 && (snake[1].getPosition().y != snake[0].getPosition().y-isquare_size)) {
                        direction = "up";
                    }
                    else if (snake.size() == 1) {
                        direction = "up";
                    }
                    //std::cout << direction << "\n";
                    //just_changed_direction = true;
                }
                //A key
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::A) {
                    if (direction != "left") {
                        sf::Time curr { clock.getElapsedTime() };
                        std::cout << "sec: " << curr.asSeconds() << "d: " << direction << "\n";
                        if (curr.asSeconds() > 0.05) {
                            just_changed_direction = true;
                            //std::cout << "sec: " << curr.asSeconds();
                            clock.restart();
                        }
                    }
                    if (snake.size() >= 2 && (snake[1].getPosition().x != snake[0].getPosition().x-isquare_size)) {
                        direction = "left";
                    }
                    else if (snake.size() == 1) {
                        direction = "left";
                    }
                    //td::cout << direction << "\n";
                }
                //S key
                if (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::S) {
                    if (direction != "down") {
                        sf::Time curr { clock.getElapsedTime() };
                        std::cout << "sec: " << curr.asSeconds() << "d: " << direction << "\n";
                        if (curr.asSeconds() > 0.05) {
                            just_changed_direction = true;
                            //std::cout << "sec: " << curr.asSeconds();
                            clock.restart();
                        }
                    }
                    if (snake.size() >= 2 && (snake[1].getPosition().y != snake[0].getPosition().y+isquare_size)) {
                        direction = "down";
                    }
                    else if (snake.size() == 1) {
                        direction = "down";
                    }
                    //std::cout << direction << "\n";
                    
                }
            }
            //game over screen, snake died, or win screen (since same buttons)
            else if ((start_game && game_over) || win_game) {
                //button functionality to play again button
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (sf::Mouse::getPosition(window).x < playagainx_ubound && 
                    sf::Mouse::getPosition(window).x > playagainx_lbound && 
                    sf::Mouse::getPosition(window).y > playagainy_lbound && 
                    sf::Mouse::getPosition(window).y < playagainy_ubound) {
                        if (game_over) {
                            game_over = false;
                        }
                        else if (win_game) {
                            win_game = false;
                        }

                        //reinitialize direction
                        direction = "up";

                        //reinitialize snake, delete all but head
                        int size = snake.size(); //if snake.size() in for condition, it's constantly deceasing
                        for (int i{ 0 }; i < (size-1); i++) {
                            snake.pop_back();
                        }
                        snake[0].setPosition(center_position);
                        
                        //reinitialize apple
                        apple_x = randomTile();
                        apple_y = randomTile();
                        while (apple_x == center_position.x && 
                        apple_y == center_position.y) { //while on the snake position
                            apple_x = randomTile();
                            apple_y = randomTile();
                        }
                        apple.setPosition({apple_x, apple_y});

                        //reinitialize picture
                        int n{ std::rand() % num_sprites };
                        curr_sprite = n;
                        //std::cout << n << "\n";
                    }

                    //button functionality for quit button
                    if (sf::Mouse::getPosition(window).x > quitbuttonx_lbound &&
                    sf::Mouse::getPosition(window).x < quitbuttonx_ubound &&
                    sf::Mouse::getPosition(window).y > quitbuttony_lbound &&
                    sf::Mouse::getPosition(window).y < quitbuttony_ubound) {
                        window.close();
                    }
                }

                //cursor change if hover play again / quit button
                if ((sf::Mouse::getPosition(window).x < playagainx_ubound && 
                sf::Mouse::getPosition(window).x > playagainx_lbound && 
                sf::Mouse::getPosition(window).y > playagainy_lbound && 
                sf::Mouse::getPosition(window).y < playagainy_ubound)
                ||
                (sf::Mouse::getPosition(window).x < quitbuttonx_ubound && 
                sf::Mouse::getPosition(window).x > quitbuttonx_lbound && 
                sf::Mouse::getPosition(window).y > quitbuttony_lbound && 
                sf::Mouse::getPosition(window).y < quitbuttony_ubound)) {
                    const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
                    window.setMouseCursor(cursor);
                    cursor_is_arrow = false;
                }
                //back to arrow if no hover
                else if (!cursor_is_arrow) {
                    const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
                    window.setMouseCursor(cursor);
                    cursor_is_arrow = true;
                }
            }
        } //end event checking
        
        //during normal play
        if (start_game && !game_over && !win_game) {
            //move snake
            sf::Time curr{ clock.getElapsedTime() };
            if (curr.asSeconds() >= 0.10 ) { //|| just_changed_direction) { //.2
                //std::cout << "d: " << direction << "\n";
                if (curr.asSeconds() >= .10) {
                    //std::cout << curr.asSeconds() << "d: " << direction << "\n";
                }
                if (just_changed_direction) {
                    //std::cout  << " d: " << direction << "\n";
                }
                if (direction == "up") {
                    if (snake[0].getPosition().y == l_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x, snake[0].getPosition().y-isquare_size, true)) {
                        game_over = true;
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
                        game_over = true;
                    }
                    else {
                        MoveSnake(snake, isquare_size, 0, just_got_body);
                    }
                }
                else if (direction == "left") {
                    if (snake[0].getPosition().x == l_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x-isquare_size, snake[0].getPosition().y, true)) {
                        game_over = true;
                    }
                    else {
                        MoveSnake(snake, -isquare_size, 0, just_got_body);
                    }
                }
                else if (direction == "down") {
                    if (snake[0].getPosition().y == u_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x, snake[0].getPosition().y+isquare_size, true)) {
                        game_over = true;
                    }
                    else {
                        MoveSnake(snake, 0, isquare_size, just_got_body);
                    }
                }
                //std::cout << curr.asSeconds() << "\n";
                clock.restart();
                if (just_changed_direction) {
                    just_changed_direction = false;
                }
            }

            //snake eats apple
            if (snake[0].getPosition() == apple.getPosition()) {
                //generate new apple
                float napple_x = randomTile(); //new apple x
                float napple_y = randomTile(); //new apple y
                //keep generating if on top of snake
                while (isOccupiedBySnake(snake, napple_x, napple_y)) {
                    napple_x = randomTile();
                    napple_y = randomTile();
                }
                apple.setPosition({napple_x, napple_y});

                //add a new square to snake
                auto tail_index{ snake.size() - 1 }; //auto because vector.size() is long long unsigned int, and i aint typing all that out
                float last_x = snake[tail_index].getPosition().x; //x position of tail
                float last_y = snake[tail_index].getPosition().y; //y position of tail
                snake.push_back(sf::RectangleShape(fsquare_vector)); //add a new rectangle
                auto ntail_index{ snake.size() - 1 }; //new tail index
                snake[ntail_index].setPosition({last_x,last_y}); //set new rectangle position to tail position
                snake[ntail_index].setOutlineColor(black);
                snake[ntail_index].setOutlineThickness(outline_thickness);
                just_got_body = true; //for move function
            }
            
            //check for win
            if (snake.size() == win_condition) {
                win_game = true;
            }
        }

        

        //display
        window.clear();
        //title screen
        if (!start_game && !game_over && !win_game) { 
            window.draw(title);
            window.draw(startbutton_bg);
            window.draw(startbutton_text);
            window.draw(instructions);            
        }
        //normal play
        else if (start_game && !game_over && !win_game) { 
            for (int i{ 0 }; i < snake.size(); i++) {
                window.draw(snake[i]);
            }
            window.draw(apple);    
        } 
        //game over screen
        else if (start_game && game_over && !win_game) {
            window.draw(gameover_text); 
            window.draw(playagain_bg);
            window.draw(playagain_text);
            window.draw(quitbutton_bg);
            window.draw(quitbutton_text);
        }
        //win screen
        else if (start_game && !game_over && win_game) {
            window.draw(win_text);
            window.draw(playagain_bg);
            window.draw(playagain_text);
            window.draw(quitbutton_bg);
            window.draw(quitbutton_text);
            window.draw(sprites[curr_sprite]);
        }
        window.display();
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

int randomTile() {
    //returns int value of random x/y position on grid
    //to maintain grid properties (like for randomly spawning apples)

    return (std::rand() % 12)*50;
}