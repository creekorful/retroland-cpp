#include <SFML/Network.hpp>
#include <iostream>

#include "../TileMap/TileMap.h"
#include "../TileMap/TileMapRenderer.h"

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

    // Players
    if (!textures[100].loadFromFile("assets/players/assassin.png", sf::IntRect(0, 0, 16, 16)))
        return std::map<int, sf::Texture>();

    return textures;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "correct usage: ./Retroland_Client <serverIp>" << std::endl;
        return 1;
    }

    sf::TcpSocket socket;
    if (socket.connect(sf::IpAddress(argv[1]), 12456) != sf::Socket::Done) {
        std::cerr << "unable to connect to " << argv[1] << ":12456" << std::endl;
        return 1;
    }

    sf::Packet packet;
    if (socket.receive(packet) != sf::Socket::Done) {
        std::cerr << "unable to receive data" << std::endl;
        socket.disconnect();
        return 1;
    }

    TileMap tileMap;
    packet >> tileMap;

    socket.disconnect();

    // Load textures
    std::map<int, sf::Texture> textures = loadTextures();
    if (textures.empty()) {
        return 1;
    }

    sf::VideoMode videoMode = sf::VideoMode::getFullscreenModes()[0];

    // Create associated map renderer
    TileMapRenderer tileMapRenderer(tileMap, sf::Vector2i(videoMode.width, videoMode.height), textures);

    sf::RenderWindow window(videoMode, "Retroland Client");
    window.setVerticalSyncEnabled(true);

    sf::Vector2i playerPos;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Close window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                sf::Vector2i oldPlayerPos = playerPos;

                switch (event.key.code) {
                    case sf::Keyboard::Z:
                        playerPos.y--;
                        break;
                    case sf::Keyboard::S:
                        playerPos.y++;
                        break;
                    case sf::Keyboard::Q:
                        playerPos.x--;
                        break;
                    case sf::Keyboard::D:
                        playerPos.x++;
                        break;
                    default:
                        break;
                }

                // Make sure movement is allowed
                int tileId = tileMap.getTile(playerPos, 1);
                if (tileId != 0) {
                    playerPos = oldPlayerPos; // not allowed
                }

                // Update player pos if changed
                if (playerPos != oldPlayerPos) {
                    tileMap.setForegroundTile(oldPlayerPos, 0);
                    tileMap.setForegroundTile(playerPos, 100);
                    tileMapRenderer.update(tileMap);
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(tileMapRenderer);
        window.display();
    }

    return 0;
}
