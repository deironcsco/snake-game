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
    std::unique_ptr<Window> window = std::make_unique<Window>( Window{ window_size_factor, window_size_px } );
    sf::RenderWindow& rw { window->getWindow() };
    
    // init game state
    std::unique_ptr<GameState> game_state = std::make_unique<GameState>( GameState{ title_screen } );

    // init style
    initStyle( *window );

    // init global control struct
    g_ctrl.game_state = game_state.get();
    g_ctrl.window = window.get();
    // Control ctrl = { gs.get(), window.get() };

    ObjectRegistry obreg{ &g_ctrl };

    StartButton sb{};
    QuitButton qb{};

    obreg.registerObject( &sb ); // TODO should sb and qb be unique_ptrs and not references? does it not matter?
    obreg.registerObject( &qb );

    while( rw.isOpen() ) {
        while( std::optional event = rw.pollEvent() ) {
            // get mouse functionality
            sf::Vector2i mouse_position{ sf::Mouse::getPosition( rw ) }; 

            // close functionality
            if ( event->is<sf::Event::Closed>() ) {
                rw.close();
            }
            
            obreg.handleEvent( event, mouse_position );
            obreg.handleHover( mouse_position );

            // test gamestate
            if ( event->is<sf::Event::MouseButtonPressed>() ) {
                std::cout << "gs " << *(g_ctrl.game_state) << "\n";
            }
        }

        // TODO when i turn this into a function, pass obreg by reference b/c i ain't copying all that by value bro
        rw.clear();
        rw.draw( obreg );
        rw.display();
    }
    return 0;
}