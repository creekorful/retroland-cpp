#include <SFML/Graphics.hpp>
#include <map>

#include "../TileMap/TileMap.h"
#include "Inventory.h"

std::map<int, sf::Texture> loadTextures()
{
    std::map<int, sf::Texture> textures;

    if (!textures[1].loadFromFile("assets/grass.png", sf::IntRect(32, 0, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[2].loadFromFile("assets/grass.png", sf::IntRect(48, 0, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[3].loadFromFile("assets/houses.png", sf::IntRect(0, 48, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[4].loadFromFile("assets/trees.png", sf::IntRect(16, 0, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[5].loadFromFile("assets/grass.png", sf::IntRect(0, 0, 16, 16)))
        return std::map<int, sf::Texture>();

    return textures;
}

int main(int argc, char *argv[])
{
    bool isBackground = true, showInventory = false;
    int currentTileId = 1;

    // Load textures
    std::map<int, sf::Texture> textures = loadTextures();
    if (textures.empty()) {
        return 1;
    }

    // Get video mode to use
    sf::VideoMode videoMode = sf::VideoMode::getFullscreenModes()[0];

    // Either create a new tilemap or load from file
    TileMap tileMap;
    if (argc == 1) {
        tileMap = TileMap(sf::Vector2i(30, 20), sf::Vector2i(videoMode.width, videoMode.height), textures);
    } else {
        std::ifstream saveFile(argv[1]);
        if (saveFile.is_open())
            tileMap = TileMap::load(saveFile, sf::Vector2i(videoMode.width, videoMode.height), textures);
        else
            return 1;
    }

    // Little GUI (current tile indicator)
    sf::RectangleShape currentTileIndicator(sf::Vector2f(200, 200));
    currentTileIndicator.setPosition(100, videoMode.height - 100 - currentTileIndicator.getSize().y);
    currentTileIndicator.setOutlineColor(sf::Color::Black);
    currentTileIndicator.setOutlineThickness(4.f);
    currentTileIndicator.setTexture(&textures[currentTileId]);

    Inventory inventory(sf::Vector2i(videoMode.width, videoMode.height), textures);

    sf::RenderWindow window(videoMode, "Retroland Editor");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Close window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                    case sf::Keyboard::Num1:
                        currentTileId = 1;
                        isBackground = true;
                        break;
                    case sf::Keyboard::Num2:
                        currentTileId = 2;
                        isBackground = true;
                        break;
                    case sf::Keyboard::Num3:
                        currentTileId = 3;
                        isBackground = false;
                        break;
                    case sf::Keyboard::Num4:
                        currentTileId = 4;
                        isBackground = false;
                        break;
                    case sf::Keyboard::Num5:
                        currentTileId = 5;
                        isBackground = true;
                        break;
                    case sf::Keyboard::X:
                        tileMap.toggleGrid();
                        break;
                    case sf::Keyboard::E:
                        showInventory = !showInventory;
                        break;
                    default:
                        break;
                }
                currentTileIndicator.setTexture(&textures[currentTileId]);
            }

            // Place tile
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2i tilePos = tileMap.getTilePosition(worldPos);

                if (isBackground)
                    tileMap.setBackgroundTile(tilePos, currentTileId);
                else
                    tileMap.setForegroundTile(tilePos, currentTileId);
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
        window.draw(currentTileIndicator);

        if (showInventory) {
            window.draw(inventory);
        }

        window.display();
    }

    return 0;
}
