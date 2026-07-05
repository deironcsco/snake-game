#include <iostream>
#include <SFML/Window.hpp>



int main() {
    sf::Window window(sf::VideoMode({800, 600}), "My window");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        // Remainder of main loop
    }

    std::cout << "hello world asdfasdfa" << '\n';
    return 0;
}


//"C:\Users\conno\Downloads\Programming\Tools\SFML-3.0.0-windows-vc17-64-bit\SFML-3.0.0\include (header files)
//"C:\Users\conno\Downloads\Programming\Tools\SFML-3.0.0-windows-vc17-64-bit\SFML-3.0.0\bin" dlls
//"C:\Users\conno\Downloads\Programming\Tools\SFML-3.0.0-windows-vc17-64-bit\SFML-3.0.0\bin\sfml-window-3.dll"