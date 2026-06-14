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


int main() {
    // init window
    unsigned int window_size_factor{ 12 }; // no magic values. e.g. 12x12 grid
    unsigned int window_size_px{ 600 }; // 600px x 600px
    std::unique_ptr<Window> window = std::make_unique<Window>( Window{ window_size_factor, window_size_px } );
    // TODO i can make this reference a member var in window so i don't have to pass it into the cursor funcs
    sf::RenderWindow& rw { window->getWindow() };
    
    // init game state
    std::unique_ptr<GameState> gs = std::make_unique<GameState>( GameState{ title_screen }); // TODO probably spell all these out lol. rw can stay
    
    // init style
    initStyle( *window );

    // init control
    g_ctrl.gs = gs.get();
    g_ctrl.w = window.get();
    // Control ctrl = { gs.get(), window.get() };

    StartButton sb{};
    QuitButton qb{};

    // // exit button
    // sf::Color red{ 200, 0, 0 };
    // unsigned int normaltext_size{ 30 }; //sf::text constructor expecting uint. this just to stop the warning

    // //quit button bg
    // sf::Vector2f quitbutton_position{300, 500}; //button position
    // float quitbutton_bgx{ 100 };
    // float quitbutton_bgy{ 75 };
    // sf::RectangleShape quitbutton_bg{{quitbutton_bgx, quitbutton_bgy}};
    // quitbutton_bg.setFillColor(red);
    // quitbutton_bg.setOutlineColor(black);
    // quitbutton_bg.setOutlineThickness(outline_thickness);
    // quitbutton_bg.setOrigin({quitbutton_bgx/2, quitbutton_bgy/2});
    // quitbutton_bg.setPosition({quitbutton_position.x, quitbutton_position.y});
    // //quit button text
    // float quitbutton_textx{ 70 };
    // float quitbutton_texty{ 35 };
    // sf::Text quitbutton_text{ font, "QUIT", normaltext_size };
    // quitbutton_text.setOrigin({quitbutton_textx/2, quitbutton_texty/2});
    // quitbutton_text.setPosition({quitbutton_position.x, quitbutton_position.y});
    // //quit button boundaries
    // float quitbuttonx_lbound{quitbutton_position.x - quitbutton_bgx/2};
    // float quitbuttonx_ubound{quitbutton_position.x + quitbutton_bgx/2};
    // float quitbuttony_lbound{quitbutton_position.y - quitbutton_bgy/2};
    // float quitbuttony_ubound{quitbutton_position.y + quitbutton_bgy/2};





    while( rw.isOpen() ) {
        while( std::optional event = rw.pollEvent() ) {
            // get mouse functionality
            int x{ sf::Mouse::getPosition(rw).x };
            int y{ sf::Mouse::getPosition(rw).y };

            // close functionality
            if ( event->is<sf::Event::Closed>() ) {
                rw.close();
            }

            // start button
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (sb.inBounds( x, y )) {
                    sb.onClick( g_ctrl );
                }
                //button functionality for quit button
                else if (qb.inBounds( x, y )) {
                    qb.onClick( g_ctrl );
                }
                std::cout << "gs: " << *gs << "\n";
            }
            
            // cursor
            if ( sb.inBounds( x, y ) ) {
                window->setCursorHand( rw );
            }
            else if ( qb.inBounds( x, y ) ) {
                window->setCursorHand( rw );
            }
            // back to normal if not hovering
            else if ( !window->getCursorIsArrow() ) {
                window->setCursorArrow( rw );
            }
        }

        // TODO turn this into a function
        rw.clear();
        rw.draw( sb );
        rw.draw( qb );
        rw.display();
    }
    return 0;
}