#include "TileMapRenderer.h"

TileMapRenderer::TileMapRenderer(const TileMap &tileMap, const sf::Vector2i &screenSize,
                                 const std::map<int, sf::Texture> &textures)
        : m_textures(textures), m_showGrid(false)
{
    int tileWidth = screenSize.x / tileMap.size().x;
    int tileHeight = screenSize.y / tileMap.size().y;
    m_tileSize = tileWidth > tileHeight ? tileWidth : tileHeight;

    m_tileDrawables[0].resize(tileMap.size().x * tileMap.size().y);
    m_tileDrawables[1].resize(tileMap.size().x * tileMap.size().y);

    for (int layer = 0; layer < 2; layer++) {
        for (int x = 0; x < tileMap.size().x; x++) {
            for (int y = 0; y < tileMap.size().y; y++) {
                int index = x * tileMap.size().y + y;

                m_tileDrawables[layer][index] = sf::RectangleShape(sf::Vector2f(m_tileSize, m_tileSize));
                m_tileDrawables[layer][index].setPosition(x * m_tileSize, y * m_tileSize);
                m_tileDrawables[layer][index].setPosition(x * m_tileSize, y * m_tileSize);

                int tileId = tileMap.getTile(sf::Vector2i(x, y), layer);
                if (tileId == 0) {
                    m_tileDrawables[layer][index].setTexture(nullptr);
                    m_tileDrawables[layer][index].setFillColor(sf::Color::Transparent);
                } else {
                    m_tileDrawables[layer][index].setTexture(&m_textures.at(tileId));
                    m_tileDrawables[layer][index].setFillColor(sf::Color::White);
                }
            }
        }
    }

    setShowGrid(m_showGrid);
}

void TileMapRenderer::update(const TileMap &tileMap)
{
    for (int layer = 0; layer < 2; layer++) {
        for (int x = 0; x < tileMap.size().x; x++) {
            for (int y = 0; y < tileMap.size().y; y++) {
                int index = x * tileMap.size().y + y;

                int tileId = tileMap.getTile(sf::Vector2i(x, y), layer);
                if (tileId == 0) {
                    m_tileDrawables[layer][index].setTexture(nullptr);
                    m_tileDrawables[layer][index].setFillColor(sf::Color::Transparent);
                } else {
                    m_tileDrawables[layer][index].setTexture(&m_textures.at(tileId));
                    m_tileDrawables[layer][index].setFillColor(sf::Color::White);
                }
            }
        }
    }
}

void TileMapRenderer::setShowGrid(bool showGrid)
{
    m_showGrid = showGrid;

    if (m_showGrid) {
        for (sf::RectangleShape &tile : m_tileDrawables[0]) {
            tile.setOutlineColor(sf::Color::Black);
            tile.setOutlineThickness(1.0f);
        }
    } else {
        for (sf::RectangleShape &tile : m_tileDrawables[0]) {
            tile.setOutlineThickness(0.f);
        }
    }
}

bool TileMapRenderer::isShowGrid() const
{
    return m_showGrid;
}

sf::Vector2i TileMapRenderer::getTilePosition(const sf::Vector2f &worldPos) const
{
    return sf::Vector2i(worldPos.x / m_tileSize, worldPos.y / m_tileSize);
}

void TileMapRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int layer = 0; layer < 2; layer++) {
        for (const auto &tile : m_tileDrawables.at(layer)) {
            target.draw(tile, states);
        }
    }
}
