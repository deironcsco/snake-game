#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main() {
    const std::optional<sf::Vector2u> windowsize_v{{600, 600}};
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Snake");
    window.setMinimumSize(windowsize_v);
    window.setMaximumSize(windowsize_v);
    std::cout << "hello world\n";

    while(window.isOpen()) {
        std::cout << "window open\n";
        while(std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
    std::cout << "Thank you!\n";
    return 0;
}