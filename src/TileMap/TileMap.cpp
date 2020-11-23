#include "TileMap.h"

TileMap::TileMap() : m_size(0, 0)
{
}

TileMap::TileMap(const sf::Vector2i &size) : m_size(size)
{
    m_tileIds[0] = std::vector(size.x * size.y, 1);
    m_tileIds[1].resize(size.x * size.y);
}

TileMap::TileMap(std::ifstream &file)
{
    // Extract map size
    file >> m_size.x;
    file >> m_size.y;

    // Extract the tiles
    int tileId = 0;
    while (file >> tileId) {
        m_tileIds[0].push_back(tileId);
        file >> tileId;
        m_tileIds[1].push_back(tileId);
    }
    file.close();
}

void TileMap::setBackgroundTile(const sf::Vector2i &pos, int tileId)
{
    setTile(pos, 0, tileId);

    // Reset foreground tile
    setForegroundTile(pos, 0);
}

void TileMap::setForegroundTile(const sf::Vector2i &pos, int tileId)
{
    setTile(pos, 1, tileId);
}

void TileMap::setTile(const sf::Vector2i &pos, int layer, int tileId)
{
    int index = pos.x * m_size.y + pos.y;
    m_tileIds[layer][index] = tileId;
}

int TileMap::getTile(const sf::Vector2i &pos, int layer) const
{
    int index = pos.x * m_size.y + pos.y;
    return m_tileIds.at(layer).at(index);
}

bool TileMap::save(std::ofstream &file) const
{
    // First of all save map size
    file << m_size.x << " " << m_size.y << " ";

    // Then save the tiles
    for (int i = 0; i < m_tileIds.at(0).size(); i++) {
        file << m_tileIds.at(0).at(i) << " " << m_tileIds.at(1).at(i) << " ";
    }

    file.close();

    return true;
}

sf::Vector2i TileMap::size() const
{
    return m_size;
}

sf::Packet &operator<<(sf::Packet &packet, const TileMap &tileMap)
{
    return packet << sf::Uint32(tileMap.m_size.x) << sf::Uint32(tileMap.m_size.y);
}

sf::Packet &operator>>(sf::Packet &packet, TileMap &tileMap)
{
    return packet >> tileMap.m_size.x >> tileMap.m_size.y;
}