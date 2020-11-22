#ifndef RETROLAND_TILEMAP_H
#define RETROLAND_TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

class TileMap : public sf::Drawable
{
public:
    TileMap();

    // Create a blank TileMap
    TileMap(const sf::Vector2i &size,
            const sf::Vector2i &screenSize,
            std::map<int, sf::Texture> &textures,
            std::map<int, std::vector<int>> tileIds = std::map<int, std::vector<int>>());

    void setBackgroundTile(const sf::Vector2i &pos, int tileId);

    void setForegroundTile(const sf::Vector2i &pos, int tileId);

    void setTile(const sf::Vector2i &pos, int layer, int tileId);

    sf::Vector2i getTilePosition(const sf::Vector2f &worldPos) const;

    static TileMap load(std::ifstream &file, const sf::Vector2i &screenSize, std::map<int, sf::Texture> &textures);

    bool save(std::ofstream &file);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    // Internal state
    sf::Vector2i m_size;
    std::map<int, std::vector<int>> m_tileIds;

    // Rendering
    int m_tileSize;
    std::map<int, sf::Texture> m_textures;
    std::map<int, std::vector<sf::RectangleShape>> m_tileDrawables;
};


#endif //RETROLAND_TILEMAP_H
