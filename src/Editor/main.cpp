#include <SFML/Graphics.hpp>
#include <map>

#include "../TileMap/TileMap.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Retroland Editor");

    TileMap tileMap(sf::Vector2i(10, 10), sf::Vector2i(1920, 1080), std::map<int, sf::Texture>());

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(tileMap);
        window.display();
    }

    return 0;
}
