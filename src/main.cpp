#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

#include "../include/Window.h"
#include "../include/Style.h"
#include "../include/StartButton.h"
#include "../include/GameState.h"
#include "../include/Button.h"
#include "../include/Control.h"
#include "../include/QuitButton.h"
#include "../include/ObjectRegistry.h"


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

    // register components to obreg
    obreg.registerObject( &sb );
    obreg.registerObject( &qb );

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
                std::cout << "gs " << static_cast<std::underlying_type<GameState>::type>(*(ctrl.game_state)) << "\n";
            }
        }

        // display
        window.display( obreg );
    }
    return 0;
}