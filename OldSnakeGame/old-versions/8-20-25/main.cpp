#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void MoveSnake(std::vector<sf::RectangleShape>&, float, float, bool&); //moves the whole snake by offset
bool isOccupiedBySnake(std::vector<sf::RectangleShape>, float, float, bool=false); //is (x,y) occupied by a snake square?
int randomTile(int, int);
bool UnlockedTrophyRoom(bool*, int);
bool CompletedTrophyRoom(bool*, int);
void WriteCodes(std::vector<std::string>, std::string, bool*, int);
bool* ReadCodes(std::vector<std::string>, std::string, bool*, int);

int main() {
    
    //simple and fast multimedia library
    
    std::srand(std::time(0)); //seed random

    //info
    //colors
    sf::Color black{ 0, 0, 0 };
    sf::Color red{ 200, 0, 0 };
    sf::Color green{ 30, 170, 0 };
    sf::Color white{ 255, 255, 255 };
    sf::Color yellow{ 255, 255, 0 };
    //font
    const sf::Font font("CaviarDreams.ttf");
    //text sizes
    unsigned int titletext_size{ 50 }; //for any text that's bigger
    unsigned int normaltext_size{ 30 }; //sf::text constructor expecting uint. this just to stop the warning
    //positions
    sf::Vector2f title_position{ 300, 200 };
    sf::Vector2f button_position{ 300, 400 };
    sf::Vector2f center_position{ 300, 300 };
    
    //300,300 is for when its 12
    //600/2
    //but when we have 150
    //there's 4 slots
    //so it's either gonna be the middle one
    //or one lower
    //600/150 = 4/2 = 2*150+75 = 375

    //misc
    int window_size{ 600 };
    unsigned int windowsize_factor { 5 }; //basically dims of window (in this case, 12x12 of squares)
    unsigned int usquare_size{ window_size/windowsize_factor }; //size of individual square in grid, unsigned int for vectors sizes
    int isquare_size{ (int)usquare_size }; //int of usquare_size, for utilizing in game and stuff (e.g. moving one square size forward/backwards)
    sf::Vector2u usquare_vector{ usquare_size, usquare_size }; //a vector of square size, unsigned int for creating window
    sf::Vector2f fsquare_vector{ usquare_vector }; //^^, float for creating shapes
    int l_bound{ isquare_size/2 }; //lower bound of map
    int u_bound{ window_size - isquare_size/2 }; //upperbound bound of map
    int win_condition{ 2 };//(int)windowsize_factor * (int)windowsize_factor }; //size of snake needed to win
    float outline_thickness{ -(float)isquare_size/10 }; //outline thickness of shapes
    //center posiition for the snake - which depends on the windowsize. the y part is +sqsz/w instead of - because it moves once before it gets drawn
    sf::Vector2f center_position_game{(std::ceil((float)windowsize_factor/2) * isquare_size)-isquare_size/2,(std::ceil((float)windowsize_factor/2) * isquare_size)+isquare_size/2};

    //game control vars
    bool just_got_body{ false }; //just ate apple (for move function, doesn't move first time)
    bool start_game{ false }; //for starting the game
    bool cursor_is_arrow{ true }; //for cursor being arrow
    bool game_over{ false }; //if game over or not
    bool win_game{ false }; //did you win the game

    //window
    sf::RenderWindow window(sf::VideoMode(windowsize_factor * usquare_vector), "Snake");
    //disable manipulating window size (cuz it fucks with graphics)
    const std::optional<sf::Vector2u> windowsize_v{windowsize_factor * usquare_vector};
    window.setMinimumSize(windowsize_v);
    window.setMaximumSize(windowsize_v);

    //snake
    std::vector<sf::RectangleShape> snake;
    snake.push_back(sf::RectangleShape(fsquare_vector)); //add head
    snake[0].setOrigin({fsquare_vector.x/2,fsquare_vector.y/2});
    snake[0].setPosition(center_position_game);
    snake[0].setOutlineColor(black);
    snake[0].setOutlineThickness(outline_thickness);

    //apple
    sf::RectangleShape apple{ fsquare_vector };
    float apple_x = randomTile((int)windowsize_factor, isquare_size);
    float apple_y = randomTile((int)windowsize_factor, isquare_size);
    while (apple_x == center_position_game.x && apple_y == center_position_game.y) { //while on the snake position
        apple_x = randomTile((int)windowsize_factor, isquare_size);
        apple_y = randomTile((int)windowsize_factor, isquare_size);
    }
    apple.setOrigin({fsquare_vector.x/2, fsquare_vector.y/2});
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
    //b overlapped at 198
    //so that means the y bounds of b should be about 100,300
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
    std::queue<std::string> direction_queue{};

    //textures
    std::vector<sf::Texture> textures{sf::Texture{"pics\\a.jpeg"},
                                    sf::Texture{"pics\\b.PNG"},
                                    sf::Texture{"pics\\bucket.jpeg"},
                                    sf::Texture{"pics\\d.jpeg"},
                                    sf::Texture{"pics\\e.jpeg"},
                                    sf::Texture{"pics\\e.png"},
                                    sf::Texture{"pics\\e.jpeg"},
                                    sf::Texture{"pics\\f.png"},
                                    sf::Texture{"pics\\j.jpg"},
                                    sf::Texture{"pics\\k.png"},
                                    sf::Texture{"pics\\k.png"},
                                    sf::Texture{"pics\\l.jpeg"},
                                    sf::Texture{"pics\\m.jpeg"},
                                    sf::Texture{"pics\\r.png"},
                                    sf::Texture{"pics\\s.png"},
                                    sf::Texture{"pics\\z.JPG"},
                                    sf::Texture{"pics\\t.png"},
                                    sf::Texture{"pics\\n.png"},
                                    sf::Texture{"pics\\r.jpeg"},
                                    sf::Texture{"pics\\b.png"},};

    std::vector<sf::Vector2f> sprite_sizes {{150,200}, //a
                                            {150,198}, //b
                                            {200,124}, //bucket
                                            {150,200}, //d
                                            {150,200}, //e
                                            {150,200}, //e
                                            {150,200}, //e
                                            {150,244}, //f
                                            {180,164}, //j
                                            {150,200}, //k
                                            {150,200}, //k
                                            {150,200}, //l
                                            {150,200}, //m
                                            {150,248}, //r
                                            {150,200}, //s
                                            {200,149}, //z
                                            {150,193}, //t
                                            {150,200}, //n
                                            {150,208}, //r
                                            {150,219} //b
                                        };
    
    //initialize sprites vector
    int counter{ 0 }; //for testing pics
    std::vector<sf::Sprite> sprites;
    sf::Vector2f sprite_pos_difference{0,54+11}; //see scratch work at line 163ish (its so it don't overlap with the win text (and is somewhat centered))
    for (int i{ 0 }; i < textures.size(); i++) {
        sprites.push_back(sf::Sprite(textures[i]));
        sprites[i].setPosition(title_position - sprite_pos_difference);
        sprites[i].setOrigin({sprite_sizes[i].x/2, sprite_sizes[i].y/2});
    }

    int num_sprites{ 20 };
    

    //codes for the file functionality
    std::vector<std::string> codes {
        "TurDuckEn", //a
        "PricsillAP", //b
        "asdfFDSA", //bucket
        "EfErvesentIN", //d
        "GlyphtraPP", //e
        "richardCarlson", //e
        "faNgruNiN", //e
        "trengSIN", //f
        "EngElk", //j
        "BaitonEs413", //k
        "creSCentM", //k
        "sanDjiOP", //l
        "MeanerstEAk", //m
        "POVcat", //r
        "CaAampere", //s
        "lmaoAsIf", //z
        "cilviaDRemo", //t
        "mobBstrUckC", //n
        "PTVFamG", //r
        "AllEnadv" //b
    };
    std::string code_filename{"codes.txt"};
    
    //trophy room
    bool trophy_room{ false }; //control variable for updating screen and stuff
    bool* obtained_trophy = new bool[num_sprites];
    for(int i{ 0 }; i < num_sprites; i++) {
        obtained_trophy[i] = false;
    }
    obtained_trophy = ReadCodes(codes, "codes.txt", obtained_trophy, num_sprites);

    int curr_sprite { std::rand() % num_sprites };
    while (obtained_trophy[curr_sprite]) {
        curr_sprite = std::rand() % num_sprites;
    }
    //back button
    float backbutton_textx{ 50 };
    float backbutton_texty{ 22 };
    sf::Text backbutton_text{ font, "BACK", 20 };
    backbutton_text.setOrigin({backbutton_textx/2, backbutton_texty/2});
    backbutton_text.setPosition({30, 585});
    sf::RectangleShape backbutton_bg{{50, 22}};
    backbutton_bg.setFillColor(red);
    backbutton_bg.setOrigin({backbutton_textx/2, backbutton_texty/2});
    backbutton_bg.setPosition({30, 585});
    int backbuttonx_ubound{ 55 };
    int backbuttonx_lbound{ 5 };
    int backbuttony_ubound{ 596 };
    int backbuttony_lbound{ 574 };

    //trophy room button
    sf::Vector2f trophyroom_pos{ 500, 570 };
    float trophyroom_textx{ 145 };
    float trophyroom_texty{ 20 };
    sf::Text trophyroom_text{font, "TROPHY ROOM", 20};
    trophyroom_text.setOrigin({trophyroom_textx/2, trophyroom_texty/2});
    trophyroom_text.setPosition(trophyroom_pos);
    trophyroom_text.setFillColor(black);
    float trophyroom_bgx{ 165 };
    float trophyroom_bgy{ 40 };
    sf::RectangleShape trophyroom_bg{{trophyroom_bgx, trophyroom_bgy}};
    trophyroom_bg.setFillColor(yellow);
    trophyroom_bg.setOrigin({trophyroom_bgx/2, trophyroom_bgy/2});
    trophyroom_bg.setPosition(trophyroom_pos);
    int trophyroomx_ubound{ 583 };
    int trophyroomx_lbound{ 417 };
    int trophyroomy_ubound{ 590 };
    int trophyroomy_lbound{ 550 };
    


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
            if (!start_game && !game_over && !win_game && !trophy_room ) { 
                
                
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


                //button functionality to start button
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (sf::Mouse::getPosition(window).x < startbuttonx_ubound && 
                    sf::Mouse::getPosition(window).x > startbuttonx_lbound && 
                    sf::Mouse::getPosition(window).y < startbuttony_ubound && 
                    sf::Mouse::getPosition(window).y > startbuttony_lbound) {
                        start_game = true;
                    }
                }

                
            
                //trophy button functionality
                if (UnlockedTrophyRoom(obtained_trophy, num_sprites)) {
                    //button press functionality
                    if (event->is<sf::Event::MouseButtonPressed>()) {
                        if (sf::Mouse::getPosition(window).x < trophyroomx_ubound && 
                        sf::Mouse::getPosition(window).x > trophyroomx_lbound && 
                        sf::Mouse::getPosition(window).y < trophyroomy_ubound && 
                        sf::Mouse::getPosition(window).y > trophyroomy_lbound) {
                            trophy_room = true;
                        }
                    }

                    //cursor change if hover (both start game and trophy room button)
                    if ((sf::Mouse::getPosition(window).x < startbuttonx_ubound && 
                    sf::Mouse::getPosition(window).x > startbuttonx_lbound && 
                    sf::Mouse::getPosition(window).y < startbuttony_ubound && 
                    sf::Mouse::getPosition(window).y > startbuttony_lbound)
                    ||
                    (sf::Mouse::getPosition(window).x < trophyroomx_ubound && 
                    sf::Mouse::getPosition(window).x > trophyroomx_lbound && 
                    sf::Mouse::getPosition(window).y < trophyroomy_ubound && 
                    sf::Mouse::getPosition(window).y > trophyroomy_lbound)) {
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
                else {
                    //cursor change if hover (just start game)
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
            }
            //normal play
            if (start_game && !game_over && !win_game && !trophy_room) { 
                //make sure cursor is arrow
                if (!cursor_is_arrow) {
                    const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value(); //.value() because optional. have to make a cursor before passing to window
                    window.setMouseCursor(cursor);
                    cursor_is_arrow = true;
                }

                //movement queueing

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
                    }                }
            }
            //game over screen, or win screen (since same buttons)
            else if (((start_game && game_over) || win_game) && !trophy_room) {
                //win game will never need the condition without trophy room...
                
                

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
                        snake[0].setPosition(center_position_game);
                        
                        //reinitialize apple
                        apple_x = randomTile((int)windowsize_factor, isquare_size);
                        apple_y = randomTile((int)windowsize_factor, isquare_size);
                        while (apple_x == center_position_game.x && 
                        apple_y == center_position_game.y) { //while on the snake position
                            apple_x = randomTile((int)windowsize_factor, isquare_size);
                            apple_y = randomTile((int)windowsize_factor, isquare_size);
                        }
                        apple.setPosition({apple_x, apple_y});

                        //reinitialize picture
                        int n{ std::rand() % num_sprites };
                        std::cout << "init n: " << n << "\n"; 
                        if (!CompletedTrophyRoom(obtained_trophy, num_sprites)) {
                            while (obtained_trophy[n] == true) { //loop to not get same picture twice
                                n = ++n % num_sprites;
                                
                                std::cout << "incr: " << n << " ";
                            }
                        }
                        std::cout << "\n";
                        curr_sprite = n;
                        //std::cout << n << "\n";
                    }

                    //button functionality for quit button
                    if (sf::Mouse::getPosition(window).x > quitbuttonx_lbound &&
                    sf::Mouse::getPosition(window).x < quitbuttonx_ubound &&
                    sf::Mouse::getPosition(window).y > quitbuttony_lbound &&
                    sf::Mouse::getPosition(window).y < quitbuttony_ubound) {
                        WriteCodes(codes, code_filename, obtained_trophy, num_sprites);
                        window.close();
                    }
                }

                //unlocked trohpy room
                if (UnlockedTrophyRoom(obtained_trophy, num_sprites)) {
                    if (event->is<sf::Event::MouseButtonPressed>()) {
                        if (sf::Mouse::getPosition(window).x < trophyroomx_ubound && 
                        sf::Mouse::getPosition(window).x > trophyroomx_lbound && 
                        sf::Mouse::getPosition(window).y > trophyroomy_lbound && 
                        sf::Mouse::getPosition(window).y < trophyroomy_ubound) {
                            trophy_room = true;
                        }
                    }

                    //cursor change if hover play again / quit button / trophy room button
                    if ((sf::Mouse::getPosition(window).x < playagainx_ubound && 
                    sf::Mouse::getPosition(window).x > playagainx_lbound && 
                    sf::Mouse::getPosition(window).y > playagainy_lbound && 
                    sf::Mouse::getPosition(window).y < playagainy_ubound)
                    ||
                    (sf::Mouse::getPosition(window).x < quitbuttonx_ubound && 
                    sf::Mouse::getPosition(window).x > quitbuttonx_lbound && 
                    sf::Mouse::getPosition(window).y > quitbuttony_lbound && 
                    sf::Mouse::getPosition(window).y < quitbuttony_ubound)
                    ||
                    (sf::Mouse::getPosition(window).x < trophyroomx_ubound && 
                    sf::Mouse::getPosition(window).x > trophyroomx_lbound && 
                    sf::Mouse::getPosition(window).y > trophyroomy_lbound && 
                    sf::Mouse::getPosition(window).y < trophyroomy_ubound)) {
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
                else {
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
            }
            //trophy room 
            else if (trophy_room) {
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (sf::Mouse::getPosition(window).x < backbuttonx_ubound && 
                    sf::Mouse::getPosition(window).x > backbuttonx_lbound && 
                    sf::Mouse::getPosition(window).y > backbuttony_lbound && 
                    sf::Mouse::getPosition(window).y < backbuttony_ubound) {
                        trophy_room = false;
                        for (int i{ 0 }; i < sprites.size(); i++) {
                            sprites[i].setScale({1, 1});
                            sprites[i].setPosition(title_position - sprite_pos_difference);
                        }
                    }
                }

                //cursor change if hover play again / quit button
                if (sf::Mouse::getPosition(window).x < backbuttonx_ubound && 
                sf::Mouse::getPosition(window).x > backbuttonx_lbound && 
                sf::Mouse::getPosition(window).y > backbuttony_lbound && 
                sf::Mouse::getPosition(window).y < backbuttony_ubound) {
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
            if (curr.asSeconds() >= 0.4) {  //.2

                //dequeueing direction
                
                if (!direction_queue.empty()) {
                    std::cout << "\ndir " << direction <<'\n';                    
                    if (snake.size() == 1) {
                        //dequeue regardless if just one body part
                        direction = direction_queue.front();
                    }
                    else if (direction == "right" && direction_queue.front() != "left" ) {
                        std::cout << "right, down\n";
                        std::cout << "head: " << snake[0].getPosition().x << ", " << snake[0].getPosition().y << "\n";
                        std::cout << "head offset: " << snake[0].getPosition().x+isquare_size << ", " << snake[0].getPosition().y+isquare_size << "\n";
                        std::cout << "2nd: " << snake[1].getPosition().x << ", " << snake[1].getPosition().y << "\n"; 
                        //only dequeue if second from head is in good spot
                        direction = direction_queue.front();
                        
                    }
                    else if (direction == "down" && direction_queue.front() != "up") {
                        direction = direction_queue.front();
                    }
                    else if (direction == "left" && direction_queue.front() != "right") {
                        std::cout << "left, up\n";
                        std::cout << "head: " << snake[0].getPosition().x << ", " << snake[0].getPosition().y << "\n";
                        std::cout << "head offset: " << snake[0].getPosition().x-isquare_size << ", " << snake[0].getPosition().y-isquare_size << "\n";
                        std::cout << "2nd: " << snake[1].getPosition().x << ", " << snake[1].getPosition().y << "\n";
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
                    //^^
                    if (snake[0].getPosition().x == l_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x-isquare_size, snake[0].getPosition().y, true)) {
                        game_over = true;
                    }
                    else {
                        MoveSnake(snake, -isquare_size, 0, just_got_body);
                    }
                }
                else if (direction == "down") {
                    //^^
                    if (snake[0].getPosition().y == u_bound || 
                    isOccupiedBySnake(snake, snake[0].getPosition().x, snake[0].getPosition().y+isquare_size, true)) {
                        game_over = true;
                    }
                    else {
                        MoveSnake(snake, 0, isquare_size, just_got_body);
                    }
                }
                
                clock.restart();
            }

            //snake eats apple
            //std::cout << "snake: " << snake[0].getPosition().x << ", " << snake[0].getPosition().y << " apples: " << apple.getPosition().x << ", " << apple.getPosition().y << "\n";
            if (snake[0].getPosition() == apple.getPosition()) {
                //generate new apple
                float napple_x = randomTile((int)windowsize_factor, isquare_size); //new apple x
                float napple_y = randomTile((int)windowsize_factor, isquare_size); //new apple y
                //keep generating if on top of snake
                while (isOccupiedBySnake(snake, napple_x, napple_y)) {
                    napple_x = randomTile((int)windowsize_factor, isquare_size);
                    napple_y = randomTile((int)windowsize_factor, isquare_size);
                }
                apple.setPosition({napple_x, napple_y});

                //add a new square to snake
                auto tail_index{ snake.size() - 1 }; //auto because vector.size() is long long unsigned int, and i aint typing all that out
                float last_x = snake[tail_index].getPosition().x; //x position of tail
                float last_y = snake[tail_index].getPosition().y; //y position of tail
                snake.push_back(sf::RectangleShape(fsquare_vector)); //add a new rectangle
                auto ntail_index{ snake.size() - 1 }; //new tail index
                snake[ntail_index].setOrigin({fsquare_vector.x/2, fsquare_vector.y/2});
                snake[ntail_index].setPosition({last_x,last_y}); //set new rectangle position to tail position
                snake[ntail_index].setOutlineColor(black);
                snake[ntail_index].setOutlineThickness(outline_thickness);
                just_got_body = true; //for move function
            }
            
            //check for win
            if (snake.size() == win_condition) {
                win_game = true;
                obtained_trophy[curr_sprite] = true; //this assignment will occur constnatly if it's win game. is there a way to just do it once
            }
        } //END during normal play

        //reset sprite scales after trophy room
        if (!trophy_room && sprites[0].getScale().x == .5) {
            for (int i{ 0 }; i < sprites.size(); i++) {
                sprites[i].setScale({1,1});
            }
        }

        //display
        window.clear();
        //title screen
        if (!start_game && !game_over && !win_game && !trophy_room) { 
            window.draw(title);
            window.draw(startbutton_bg);
            window.draw(startbutton_text);
            window.draw(instructions);
            //window.draw(sprites[counter]); //for testing pics 
            if (UnlockedTrophyRoom(obtained_trophy, num_sprites)) {
                window.draw(trophyroom_bg);
                window.draw(trophyroom_text);
            }

        }
        //normal play
        else if (start_game && !game_over && !win_game && !trophy_room) { 
            for (int i{ 0 }; i < snake.size(); i++) {
                window.draw(snake[i]);
            }
            window.draw(apple);    
        } 
        //game over screen
        else if (start_game && game_over && !win_game && !trophy_room) {
            window.draw(gameover_text); 
            window.draw(playagain_bg);
            window.draw(playagain_text);
            window.draw(quitbutton_bg);
            window.draw(quitbutton_text);
            if (UnlockedTrophyRoom(obtained_trophy, num_sprites)) {
                window.draw(trophyroom_bg);
                window.draw(trophyroom_text);
            }
        }
        //win screen
        else if (start_game && !game_over && win_game && !trophy_room) {
            window.draw(win_text);
            window.draw(playagain_bg);
            window.draw(playagain_text);
            window.draw(quitbutton_bg);
            window.draw(quitbutton_text);
            window.draw(sprites[curr_sprite]);
            if (UnlockedTrophyRoom(obtained_trophy, num_sprites)) {
                window.draw(trophyroom_bg);
                window.draw(trophyroom_text);
            }
        }
        //trophy room
        else if (trophy_room) {
            float x{ 60 }; //after .5 scale max width is 100 and height 125, so origin is at 50 62, so 60 72 for the padding
            float y{ 72 };
            for (int i{ 0 }; i < sprites.size(); i++) {
                sprites[i].setScale({.5, .5});
                sprites[i].setPosition({x, y});
                
                
                if (obtained_trophy[i] == true) {
                    window.draw(sprites[i]);
                }
                else {
                    sf::RectangleShape empty_sprite{{100, 125}};
                    empty_sprite.setOrigin({50, 62});
                    empty_sprite.setFillColor(black);
                    empty_sprite.setOutlineColor(white);
                    empty_sprite.setOutlineThickness(outline_thickness);
                    empty_sprite.setPosition({x, y});
                    window.draw(empty_sprite);

                    sf::Texture question_texture{ "pics\\question.JPG" };
                    sf::Sprite question{ question_texture };
                    question.setOrigin({80/2, 113/2});
                    question.setPosition({x, y});
                    window.draw(question);
                }
                //update positions
                x += 120; //next entry
                if ((i+1) % 5 == 0) { //go down a row
                    x = 60;
                    y += 144;
                }
                
                window.draw(backbutton_bg);
                window.draw(backbutton_text);
            }
        }
        window.display();
    }

    delete[] obtained_trophy;
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

int randomTile(int num_squares, int square_size) {
    //returns int value of random x/y position on grid
    //to maintain grid properties (like for randomly spawning apples)

    return ((std::rand() % num_squares)*square_size) + square_size/2;
}

bool UnlockedTrophyRoom(bool* obtained_trophy, int size) {
    for (int i{ 0 }; i < size; i++) {
        if (obtained_trophy[i] == true) {
            return true;
        }
    }
    return false;
}

bool CompletedTrophyRoom(bool* obtained_trophy, int size) {
    for (int i{ 0 }; i < size; i++) {
        std::cout << "CTR: i: " << i << " ot[i]: " << obtained_trophy[i] << "\n";
        if (obtained_trophy[i] == false) {
            return false;
        }
    }
    return true;
}

void WriteCodes(std::vector<std::string> codes, std::string filename, bool* obtained_trophy, int ot_size) {
    //open file
    std::ofstream file(filename);

    //write codes to file if obtained_trophy is true
    for (int i{ 0 }; i < ot_size; i++) {
        if (obtained_trophy[i]) { //^ but for ot
            file << codes[i] << "\n";
        }
        
    }

    //close file
    file.close();
    return;
}

bool* ReadCodes(std::vector<std::string> codes, std::string filename, bool* obtained_trophy, int ot_size) {
    std::ifstream i_file(filename);
    
    //for length of file
    while (!i_file.eof()) {
        
        //read line
        std::string line{ "" };
        std::getline(i_file, line);
        
        //if it exists in codes, then set o_t to true
        for (int i{ 0 }; i < ot_size; i++) {
            if (line == codes[i]) {
                obtained_trophy[i] = true;
            }
        }
    }
    return obtained_trophy;
}