#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../include/Window.h"
#include "../include/Style.h"


enum game_state {
    title_screen,
    start_game
};

int main() {

    unsigned int window_size_factor{ 12 }; // no magic values. e.g. 12x12 grid
    unsigned int window_size_px{ 600 }; // 600px x 600px
    
    Window window{ window_size_factor, window_size_px };
    sf::RenderWindow& rw = window.getWindow();
   
    game_state gs = title_screen;
    
    initStyle(window);
    
    // START BUTTON
    // start button bg
    float startbutton_bgx{ 150 };
    float startbutton_bgy{ 100 };
    sf::RectangleShape startbutton_bg({startbutton_bgx, startbutton_bgy});
    startbutton_bg.setFillColor(green);
    startbutton_bg.setOutlineColor(black);
    startbutton_bg.setOutlineThickness(outline_thickness);
    startbutton_bg.setOrigin({startbutton_bgx/2, startbutton_bgy/2}); // half of its dimensions
    startbutton_bg.setPosition(button_position);
    // start button text
    float startbutton_textx{ 80 };
    float startbutton_texty{ 30 };
    sf::Text startbutton_text(font, "START", normal_text_size);
    startbutton_text.setOrigin({startbutton_textx/2, startbutton_texty/2});
    startbutton_text.setPosition(button_position);
    // start button boundaries
    float startbuttonx_lbound{ button_position.x - startbutton_bgx/2 }; // origin +- half of size
    float startbuttonx_ubound{ button_position.x + startbutton_bgx/2 };
    float startbuttony_lbound{ button_position.y - startbutton_bgy/2 };
    float startbuttony_ubound{ button_position.y + startbutton_bgy/2 };

    while( rw.isOpen() ) {
        while( std::optional event = rw.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                rw.close();
            }

            //button functionality to start button
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (sf::Mouse::getPosition(rw).x < startbuttonx_ubound && 
                sf::Mouse::getPosition(rw).x > startbuttonx_lbound && 
                sf::Mouse::getPosition(rw).y < startbuttony_ubound && 
                sf::Mouse::getPosition(rw).y > startbuttony_lbound) {
                    gs = start_game;
                }
                std::cout << "gs: " << gs << "\n";
            }

            if (sf::Mouse::getPosition(rw).x < startbuttonx_ubound && 
            sf::Mouse::getPosition(rw).x > startbuttonx_lbound && 
            sf::Mouse::getPosition(rw).y < startbuttony_ubound && 
            sf::Mouse::getPosition(rw).y > startbuttony_lbound) {
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value(); //.value() because optional. have to make a cursor before passing to window
                rw.setMouseCursor(cursor);
                window.setCursorIsArrow(false);
            }
            // back to normal if not hovering
            else if (!window.getCursorIsArrow()) {
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value(); //.value() because optional. have to make a cursor before passing to window
                rw.setMouseCursor(cursor);
                window.setCursorIsArrow(true);
            }

            
        }
        rw.clear();
        rw.draw( startbutton_bg );
        rw.draw( startbutton_text );
        rw.display();
    }
    return 0;
}