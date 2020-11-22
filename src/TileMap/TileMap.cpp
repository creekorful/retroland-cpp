#include "TileMap.h"

TileMap::TileMap(const sf::Vector2i &mapSize, const sf::Vector2i &screenSize,
                 const std::map<int, sf::Texture> &textures)
        : m_textures(textures)
{
    int tileWidth = screenSize.x / mapSize.x;
    int tileHeight = screenSize.y / mapSize.y;
    int blockSize = tileWidth > tileHeight ? tileWidth : tileHeight;

    m_backgroundTiles.resize(mapSize.x * mapSize.y);
    m_foregroundTiles.resize(mapSize.x * mapSize.y);

    for (int x = 0; x < mapSize.x; x++) {
        for (int y = 0; y < mapSize.y; y++) {
            sf::RectangleShape tile(sf::Vector2f(blockSize, blockSize));
            tile.setPosition(x * blockSize, y * blockSize);
            tile.setOutlineColor(sf::Color::Black);
            tile.setOutlineThickness(1.0f);
            tile.setTexture(&m_textures[0]);

            m_backgroundTiles.push_back(tile);
        }
    }
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &backgroundTile : m_backgroundTiles) {
        target.draw(backgroundTile, states);
    }
}
