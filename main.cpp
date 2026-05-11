#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main() {

    // window control 
    int window_size{ 600 }; // pixel size
    unsigned int windowsize_factor { 12 }; // how many squares there are for snake (e.g. wsf = 12 means 12x12 grid)
    unsigned int usquare_size{ window_size / windowsize_factor }; // pixel size of the squares, unsigned int
    sf::Vector2u usquare_vector{ usquare_size, usquare_size }; // vector of square size
    int isquare_size{ (int)usquare_size }; // usquare_size as int
    sf::RenderWindow window( sf::VideoMode( windowsize_factor * usquare_vector ), "Snake" );
    //disable manipulating window size (cuz it fucks with graphics)
    const std::optional<sf::Vector2u> windowsize_v{ windowsize_factor * usquare_vector };
    window.setMinimumSize( windowsize_v );
    window.setMaximumSize( windowsize_v );
    // does this go in window shit?
    bool cursor_is_arrow{ true }; //for cursor being arrow
   
    // control
    bool start_game{ false };
    
    
    // styling and for making componenets
    sf::Color green{ 30, 170, 0 };
    sf::Color black{ 0, 0, 0 };
    sf::Vector2f button_position{ 300, 400 };
    float outline_thickness{ -(float)isquare_size / 10 };
    const sf::Font font("CaviarDreams.ttf");
    unsigned int normaltext_size{ 30 };




    // START BUTTON
    // start button bg
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

    while( window.isOpen() ) {
        while( std::optional event = window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                window.close();
            }

            //button functionality to start button
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (sf::Mouse::getPosition(window).x < startbuttonx_ubound && 
                sf::Mouse::getPosition(window).x > startbuttonx_lbound && 
                sf::Mouse::getPosition(window).y < startbuttony_ubound && 
                sf::Mouse::getPosition(window).y > startbuttony_lbound) {
                    start_game = true;
                }
                std::cout << "start_game: " << start_game << "\n";
            }

            if (sf::Mouse::getPosition(window).x < startbuttonx_ubound && 
            sf::Mouse::getPosition(window).x > startbuttonx_lbound && 
            sf::Mouse::getPosition(window).y < startbuttony_ubound && 
            sf::Mouse::getPosition(window).y > startbuttony_lbound) {
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value(); //.value() because optional. have to make a cursor before passing to window
                window.setMouseCursor(cursor);
                cursor_is_arrow = false;
            }
            // back to normal if not hovering
            else if (!cursor_is_arrow) {
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value(); //.value() because optional. have to make a cursor before passing to window
                window.setMouseCursor(cursor);
                cursor_is_arrow = true;
            }

            
        }
        window.clear();
        window.draw( startbutton_bg );
        window.draw( startbutton_text );
        window.display();
    }
    return 0;
}