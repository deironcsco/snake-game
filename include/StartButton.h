#ifndef startbutton_h
#define startbutton_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Style.h"
#include "Bound.h"
#include "GameState.h"

class StartButton : public sf::Drawable {
private:
    // background object
    sf::Vector2f bg_v{ 150, 100 };
    sf::RectangleShape bg{ bg_v };

    // text object
    sf::Vector2f text_v{ 80, 30 };
    sf::Text text{ font, "START", normal_text_size };
    
    // boundaries
    // origin +- half of size
    Bound bnd = {
        button_position.x + bg_v.x / 2,
        button_position.x - bg_v.x / 2,
        button_position.y + bg_v.y / 2,
        button_position.y - bg_v.y / 2,
    };

public:
    StartButton();
    bool inBounds( int, int );
    sf::RectangleShape& getBg();
    sf::Text& getText();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void onClick(GameState&);
};

#endif