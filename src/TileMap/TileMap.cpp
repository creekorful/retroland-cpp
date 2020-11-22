#include "TileMap.h"

TileMap::TileMap() = default;

TileMap::TileMap(const sf::Vector2i &size, const sf::Vector2i &screenSize,
                 std::map<int, sf::Texture> &textures, std::map<int, std::vector<int>> tileIds)
        : m_textures(std::move(textures)), m_size(size)
{
    int tileWidth = screenSize.x / size.x;
    int tileHeight = screenSize.y / size.y;
    m_tileSize = tileWidth > tileHeight ? tileWidth : tileHeight;

    m_tileDrawables[0].resize(size.x * size.y);
    m_tileDrawables[1].resize(size.x * size.y);

    if (tileIds.empty()) {
        m_tileIds[0] = std::vector(size.x * size.y, 1);
        m_tileIds[1].resize(size.x * size.y);
    } else {
        m_tileIds = std::move(tileIds);
    }

    for (int layer = 0; layer < 2; layer++) {
        for (int x = 0; x < size.x; x++) {
            for (int y = 0; y < size.y; y++) {
                int index = x * m_size.y + y;

                m_tileDrawables[layer][index] = sf::RectangleShape(sf::Vector2f(m_tileSize, m_tileSize));
                m_tileDrawables[layer][index].setPosition(x * m_tileSize, y * m_tileSize);
                m_tileDrawables[layer][index].setPosition(x * m_tileSize, y * m_tileSize);

                if (layer == 0) {
                    m_tileDrawables[layer][index].setOutlineColor(sf::Color::Black);
                    m_tileDrawables[layer][index].setOutlineThickness(1.0f);
                }

                if (m_tileIds[layer][index] != 0) {
                    m_tileDrawables[layer][index].setTexture(&m_textures.at(m_tileIds[layer][index]));
                } else {
                    m_tileDrawables[layer][index].setTexture(nullptr);
                    m_tileDrawables[layer][index].setFillColor(sf::Color::Transparent);
                }
            }
        }
    }
}

void TileMap::setBackgroundTile(const sf::Vector2i &pos, int tileId)
{
    int index = pos.x * m_size.y + pos.y;
    m_tileDrawables[0][index].setTexture(&m_textures.at(tileId));
    m_tileIds[0][index] = tileId;

    // Reset foreground tile
    m_tileDrawables[1][index].setTexture(nullptr);
    m_tileDrawables[1][index].setFillColor(sf::Color::Transparent);
    m_tileIds[1][index] = 0;
}

void TileMap::setForegroundTile(const sf::Vector2i &pos, int tileId)
{
    int index = pos.x * m_size.y + pos.y;
    m_tileDrawables[1][index].setTexture(&m_textures.at(tileId));
    m_tileDrawables[1][index].setFillColor(sf::Color::White);
    m_tileIds[1][index] = tileId;
}

sf::Vector2i TileMap::getTilePosition(const sf::Vector2i &screenPosition) const
{
    return screenPosition / m_tileSize;
}

TileMap TileMap::load(std::ifstream &file, const sf::Vector2i &screenSize, std::map<int, sf::Texture> &textures)
{
    sf::Vector2i size;
    std::map<int, std::vector<int>> tileIds;

    // Extract map size
    file >> size.x;
    file >> size.y;

    // Extract the tiles
    int tileId = 0;
    while (file >> tileId) {
        tileIds[0].push_back(tileId);
        file >> tileId;
        tileIds[1].push_back(tileId);
    }
    file.close();

    return TileMap(size, screenSize, textures, tileIds);
}

bool TileMap::save(std::ofstream &file)
{
    // First of all save map size
    file << m_size.x << " " << m_size.y << " ";

    // Then save the tiles
    for (int i = 0; i < m_tileIds[0].size(); i++) {
        file << m_tileIds[0][i] << " " << m_tileIds[1][i] << " ";
    }

    file.close();

    return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &backgroundTile : m_tileDrawables.at(0)) {
        target.draw(backgroundTile, states);
    }

    for (const auto &foregroundTile : m_tileDrawables.at(1)) {
        target.draw(foregroundTile, states);
    }
}

