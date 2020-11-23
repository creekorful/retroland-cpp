#include <SFML/Graphics.hpp>
#include <map>

#include "../TileMap/TileMap.h"
#include "Inventory.h"

std::map<int, sf::Texture> loadTextures()
{
    std::map<int, sf::Texture> textures;

    // Grass
    if (!textures[1].loadFromFile("assets/grass.png", sf::IntRect(32, 0, 16, 16)))
        return std::map<int, sf::Texture>();

    // Road
    if (!textures[20].loadFromFile("assets/grass.png", sf::IntRect(48, 0, 16, 16)))
        return std::map<int, sf::Texture>();

    // Water
    if (!textures[30].loadFromFile("assets/grass.png", sf::IntRect(0, 0, 16, 16)))
        return std::map<int, sf::Texture>();

    // Trees
    if (!textures[40].loadFromFile("assets/trees.png", sf::IntRect(16, 0, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[41].loadFromFile("assets/trees.png", sf::IntRect(32, 0, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[42].loadFromFile("assets/trees.png", sf::IntRect(48, 0, 16, 16)))
        return std::map<int, sf::Texture>();

    // Houses
    if (!textures[50].loadFromFile("assets/houses.png", sf::IntRect(0, 48, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[51].loadFromFile("assets/houses.png", sf::IntRect(16, 48, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[52].loadFromFile("assets/houses.png", sf::IntRect(32, 48, 16, 16)))
        return std::map<int, sf::Texture>();

    // Walls
    if (!textures[60].loadFromFile("assets/towers.png", sf::IntRect(16, 16, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[61].loadFromFile("assets/towers.png", sf::IntRect(16, 32, 16, 16)))
        return std::map<int, sf::Texture>();
    if (!textures[62].loadFromFile("assets/towers.png", sf::IntRect(0, 32, 16, 16)))
        return std::map<int, sf::Texture>();

    return textures;
}

bool isBackgroundTile(int tileId)
{
    return tileId == 1 || tileId == 2 || tileId == 5;
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
                    case sf::Keyboard::X:
                        tileMap.toggleGrid();
                        break;
                    case sf::Keyboard::E:
                        showInventory = !showInventory;
                        break;
                        // Save system
                    case sf::Keyboard::S:
                        if (event.key.control) {
                            std::ofstream saveFile("save.dat");
                            if (saveFile.is_open()) {
                                tileMap.save(saveFile);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (showInventory) {
                    int tileId = inventory.getTileId(worldPos);
                    if (tileId != -1) {
                        currentTileId = tileId;
                        isBackground = isBackgroundTile(currentTileId);
                        currentTileIndicator.setTexture(&textures[currentTileId]);
                        showInventory = false;
                    }
                } else {
                    sf::Vector2i tilePos = tileMap.getTilePosition(worldPos);

                    if (isBackground)
                        tileMap.setBackgroundTile(tilePos, currentTileId);
                    else
                        tileMap.setForegroundTile(tilePos, currentTileId);
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
