#include "TileMap.h"

TileMap::TileMap(const sf::Vector2i &mapSize, const sf::Vector2i &screenSize,
                 const std::map<int, sf::Texture> &textures)
{
    int tileWidth = screenSize.x / mapSize.x;
    int tileHeight = screenSize.y / mapSize.y;
    int blockSize = tileWidth > tileHeight ? tileWidth : tileHeight;

    for (int x = 0; x < mapSize.x; x++) {
        for (int y = 0; y < mapSize.y; y++) {
            sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
            shape.setPosition(x * blockSize, y * blockSize);
            shape.setFillColor(sf::Color::Red);
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1.0f);

            m_backgroundTiles.push_back(shape);
        }
    }
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &backgroundTile : m_backgroundTiles) {
        target.draw(backgroundTile, states);
    }
}
