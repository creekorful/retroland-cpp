#include "TileMap.h"

TileMap::TileMap(const sf::Vector2i &size, const sf::Vector2i &screenSize,
                 std::map<int, sf::Texture> &textures)
        : m_textures(std::move(textures)), m_size(size)
{
    int tileWidth = screenSize.x / size.x;
    int tileHeight = screenSize.y / size.y;
    m_blockSize = tileWidth > tileHeight ? tileWidth : tileHeight;

    m_backgroundTiles.resize(size.x * size.y);

    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            int index = x * m_size.y + y;

            m_backgroundTiles[index] = sf::RectangleShape(sf::Vector2f(m_blockSize, m_blockSize));
            m_backgroundTiles[index].setPosition(x * m_blockSize, y * m_blockSize);
            m_backgroundTiles[index].setOutlineColor(sf::Color::Black);
            m_backgroundTiles[index].setOutlineThickness(1.0f);
            m_backgroundTiles[index].setTexture(&m_textures.at(0));
            m_backgroundTiles[index].setPosition(x * m_blockSize, y * m_blockSize);
        }
    }
}

void TileMap::setBackgroundTile(const sf::Vector2i &pos, int tileId)
{
    int index = pos.x * m_size.y + pos.y;
    m_backgroundTiles[index].setTexture(&m_textures.at(tileId));
}

sf::Vector2i TileMap::getBlockPosition(const sf::Vector2i &screenPosition) const
{
    return screenPosition / m_blockSize;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &backgroundTile : m_backgroundTiles) {
        target.draw(backgroundTile, states);
    }
}
