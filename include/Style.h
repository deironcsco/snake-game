#include <SFML/Graphics.hpp>
#include "Window.h"

// styling and for making componenets

// colors
sf::Color green{ 30, 170, 0 };
sf::Color black{ 0, 0, 0 };

// positions
sf::Vector2f button_position{ 300, 400 };

// outline thickness for shapes
float outline_thickness;

// shapes
const sf::Font font("CaviarDreams.ttf");

// text size
unsigned int normal_text_size{ 30 };

// since outline thickness is dependent on the grid size of the window
void initStyle(Window& window) {
    outline_thickness = -window.getSquareSize<float>() / 10;
}