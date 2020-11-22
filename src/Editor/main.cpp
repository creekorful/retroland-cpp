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

int main(int argc, char *argv[])
{
    // Load textures
    std::map<int, sf::Texture> textures = loadTextures();
    if (textures.empty()) {
        return 1;
    }

    // Either create a new tilemap or load from file
    TileMap tileMap;
    if (argc == 1) {
        tileMap = TileMap(sf::Vector2i(30, 20), sf::Vector2i(1920, 1080), textures);
    } else {
        std::ifstream saveFile(argv[1]);
        if (saveFile.is_open())
            tileMap = TileMap::load(saveFile, sf::Vector2i(1920, 1080), textures);
        else
            return 1;
    }

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Retroland Editor");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Close window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Place tile
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i tilePos = tileMap.getTilePosition(sf::Mouse::getPosition(window));
                tileMap.setBackgroundTile(tilePos, 1);
            }

            // Save
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S && event.key.control) {
                    std::ofstream saveFile("save.dat");
                    if (saveFile.is_open()) {
                        tileMap.save(saveFile);
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(tileMap);
        window.display();
    }

    return 0;
}
