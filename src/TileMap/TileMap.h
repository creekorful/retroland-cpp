#ifndef RETROLAND_TILEMAP_H
#define RETROLAND_TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable
{
public:
    // Create a blank TileMap
    TileMap(const sf::Vector2i &mapSize,
            const sf::Vector2i &screenSize,
            const std::map<int, sf::Texture> &textures);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::map<int, sf::Texture> m_textures;
    std::vector<sf::RectangleShape> m_backgroundTiles;
    std::vector<sf::RectangleShape> m_foregroundTiles;
};


#endif //RETROLAND_TILEMAP_H
