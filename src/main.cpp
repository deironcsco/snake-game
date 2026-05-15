#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../include/Window.h"
#include "../include/Style.h"
#include "../include/StartButton.h"


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
    
    StartButton sb = StartButton();

    // TODO onClick for sb
    // TODO window cursor manip

    while( rw.isOpen() ) {
        while( std::optional event = rw.pollEvent() ) {
            int x{ sf::Mouse::getPosition(rw).x };
            int y{ sf::Mouse::getPosition(rw).y };

            if ( event->is<sf::Event::Closed>() ) {
                rw.close();
            }

            //button functionality to start button
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (sb.inBounds(x, y)) {
                    gs = start_game;
                }
                std::cout << "gs: " << gs << "\n";
            }

            if (sb.inBounds(x, y)) {
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
        rw.draw( sb.getBg() );
        rw.draw( sb.getText() );
        rw.display();
    }
    return 0;
}