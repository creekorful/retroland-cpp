#include <SFML/Graphics.hpp>
#include <map>

#include "../TileMap/TileMap.h"

std::map<int, sf::Texture> loadTextures()
{
    std::map<int, sf::Texture> textures;

    if (!textures[0].loadFromFile("assets/grass.png", sf::IntRect(32, 0, 16, 16))) {
        return std::map<int, sf::Texture>();
    }

    if (!textures[1].loadFromFile("assets/grass.png", sf::IntRect(48, 0, 16, 16))) {
        return std::map<int, sf::Texture>();
    }

    return textures;
}

int main()
{
    // Load textures
    std::map<int, sf::Texture> textures = loadTextures();
    if (textures.empty()) {
        return 1;
    }
    TileMap tileMap(sf::Vector2i(30, 20), sf::Vector2i(1920, 1080), textures);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Retroland Editor");
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Place block
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i blockPos = tileMap.getBlockPosition(sf::Mouse::getPosition(window));
                tileMap.setBackgroundTile(blockPos, 1);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(tileMap);
        window.display();
    }

    return 0;
}
