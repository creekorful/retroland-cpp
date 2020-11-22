#include "TileMap.h"

TileMap::TileMap() = default;

TileMap::TileMap(const sf::Vector2i &size, const sf::Vector2i &screenSize,
                 std::map<int, sf::Texture> &textures, std::vector<int> tileIds)
        : m_textures(std::move(textures)), m_size(size)
{
    int tileWidth = screenSize.x / size.x;
    int tileHeight = screenSize.y / size.y;
    m_tileSize = tileWidth > tileHeight ? tileWidth : tileHeight;

    m_tileDrawables.resize(size.x * size.y);

    if (tileIds.empty()) {
        m_tileIds.resize(size.x * size.y);
    } else {
        m_tileIds = std::move(tileIds);
    }

    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            int index = x * m_size.y + y;

            m_tileDrawables[index] = sf::RectangleShape(sf::Vector2f(m_tileSize, m_tileSize));
            m_tileDrawables[index].setPosition(x * m_tileSize, y * m_tileSize);
            m_tileDrawables[index].setOutlineColor(sf::Color::Black);
            m_tileDrawables[index].setOutlineThickness(1.0f);
            m_tileDrawables[index].setTexture(&m_textures.at(m_tileIds[index]));
            m_tileDrawables[index].setPosition(x * m_tileSize, y * m_tileSize);
        }
    }
}

void TileMap::setBackgroundTile(const sf::Vector2i &pos, int tileId)
{
    int index = pos.x * m_size.y + pos.y;
    m_tileDrawables[index].setTexture(&m_textures.at(tileId));
    m_tileIds[index] = tileId;
}

sf::Vector2i TileMap::getTilePosition(const sf::Vector2i &screenPosition) const
{
    return screenPosition / m_tileSize;
}

TileMap TileMap::load(std::ifstream &file, const sf::Vector2i &screenSize, std::map<int, sf::Texture> &textures)
{
    sf::Vector2i size;
    std::vector<int> tileIds;

    // Extract map size
    file >> size.x;
    file >> size.y;

    // Extract the tiles
    int tileId = 0;
    while (file >> tileId) {
        tileIds.push_back(tileId);
    }
    file.close();

    return TileMap(size, screenSize, textures, tileIds);
}

bool TileMap::save(std::ofstream &file)
{
    // First of all save map size
    file << m_size.x << " " << m_size.y << " ";

    // Then save the tiles
    for (int tileId : m_tileIds) {
        file << tileId << " ";
    }

    file.close();

    return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &backgroundTile : m_tileDrawables) {
        target.draw(backgroundTile, states);
    }
}

