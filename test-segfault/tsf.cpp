// first cd into test-segfault
// g++ -g tsf.cpp ../src/Button.cpp ../src/StartButtonNew.cpp ../src/Window.cpp -I../include -I/c/Users/conno/SFML-3.0.0/include -L/c/Users/conno/SFML-3.0.0/lib -lsfml-graphics -lsfml-window -lsfml-system -o ../bin/tsf.exe

// SFML_ROOT="/c/Users/conno/SFML-3.0.0"
// SFML_INCLUDE="-I${SFML_ROOT}/include -L${SFML_ROOT}/lib -lsfml-graphics -lsfml-window -lsfml-system"

// context: i was getting a segfault and i thought i should create a minimal example to play around with it
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../include/Window.h"
// #include "../include/StartButtonNew.h"
#include "../include/GameState.h"
#include "../include/Style.h"
#include <iostream>

int main() {

    Window w { 12, 600 };
    sf::RenderWindow& rw = w.getRenderWindow();

    GameState gs { title_screen };

    // Control ctrl {
    //     gs, w
    // };


    //text test

    // normal, raw
    sf::Font f{ "CaviarDreams.ttf" }; 
    sf::Text t{ f, "TEXT", 30 };

    // pointer
    sf::Text* tp;
    tp = new sf::Text{f, "TEXT", 30};

    // with bp.font
    sf::Text t2{ font, "TEXT", normal_text_size };

    // pointer with bp.font but raw text
    sf::Text* tp3;
    tp3 = new sf::Text{font, "TEXT", 30};

    // pointer with f but normaltext size
    sf::Text* tp4;
    tp4 = new sf::Text{f, "TEXT", normal_text_size};

    // pointer with bp.font
    sf::Text* tp2;
    tp2 = new sf::Text{font, "TEXT", normal_text_size};

    delete tp, tp3, tp4, tp2;


    sf::Font f10{ "CaviarDreams.ttf" };
    sf::Text t10{ f10, "TEXT", 30 };
    auto tex = t10.getFont().getTexture( 10 );
    std::cout << "size " << tex.getSize().x << ", " << tex.getSize().y << "\n";
    sf::Text t11{ font, "TEXT", 30 };
    tex = t11.getFont().getTexture( 10 );
    std::cout << "t11 " << tex.getSize().x << ", " << tex.getSize().y << "\n";
    sf::Text t12{ font, "TEXT", normal_text_size };
    tex = t12.getFont().getTexture( 10 );
    std::cout << "t12 " << tex.getSize().x << ", " << tex.getSize().y << "\n";
    tex = t12.getFont().getTexture( 30 );
    std::cout << "t12 30" << tex.getSize().x << ", " << tex.getSize().y << "\n";


    // ButtonParams* bp { new ButtonParams {
    //     { 150, 100 },
    //     { 80, 30 },
    //     normal_text_size,
    //     "START",
    //     font,
    //     button_position,
    //     green,
    //     black,
    //     outline_thickness,
    //     ctrl
    // } };

    // StartButton sb { bp };

    while ( rw.isOpen() ) {
        while ( auto event = rw.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                rw.close();
            }
        }
        rw.clear();
        // rw.draw( sb );
        rw.display();
    }

    // delete bp;

    return 0;
}