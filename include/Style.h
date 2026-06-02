#ifndef STYLE_H
#define STYLE_H

#include <SFML/Graphics.hpp>
#include "Window.h"

// styling and for making components
// TODO - make it a namespace? so i know where they're coming from?

// colors
inline sf::Color green{ 30, 170, 0 };
inline sf::Color black{ 0, 0, 0 };

// positions
inline sf::Vector2f button_position{ 300, 400 };

// outline thickness for shapes
inline float outline_thickness;

// shapes
inline const sf::Font font( "CaviarDreams.ttf" );

// text size
inline unsigned int normal_text_size{ 30 };

// since outline thickness is dependent on the grid size of the window
inline void initStyle( Window& window ) {
    outline_thickness = -window.getSquareSize<float>() / 10;
}

#endif