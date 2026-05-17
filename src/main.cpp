#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../include/Window.h"
#include "../include/Style.h"
#include "../include/StartButton.h"
#include "../include/GameState.h"


int main() {

    // init window
    unsigned int window_size_factor{ 12 }; // no magic values. e.g. 12x12 grid
    unsigned int window_size_px{ 600 }; // 600px x 600px
    Window window{ window_size_factor, window_size_px };
    sf::RenderWindow& rw = window.getWindow();
    
    // init game state
    GameState gs = title_screen;
    
    // init style
    initStyle( window );
    
    // create a start button
    StartButton sb = StartButton();

    while( rw.isOpen() ) {
        while( std::optional event = rw.pollEvent() ) {
            // get mouse functionality
            int x{ sf::Mouse::getPosition(rw).x };
            int y{ sf::Mouse::getPosition(rw).y };

            // close functionality
            if ( event->is<sf::Event::Closed>() ) {
                rw.close();
            }

            // button functionality to start button
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (sb.inBounds( x, y )) {
                    sb.onClick( gs );
                }
                std::cout << "gs: " << gs << "\n";
            }
            
            // cursor
            if ( sb.inBounds( x, y ) ) {
                window.setCursorHand( rw );
            }
            // back to normal if not hovering
            else if ( !window.getCursorIsArrow() ) {
                window.setCursorArrow( rw );
            }
        }

        // TODO turn this into a function
        rw.clear();
        rw.draw( sb );
        rw.display();
    }
    return 0;
}