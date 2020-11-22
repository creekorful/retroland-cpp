#ifndef RETROLAND_TILEMAP_H
#define RETROLAND_TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable
{
public:
    // Create a blank TileMap
    TileMap(const sf::Vector2i &size,
            const sf::Vector2i &screenSize,
            std::map<int, sf::Texture> &textures);

    void setBackgroundTile(const sf::Vector2i &pos, int tileId);

    sf::Vector2i getBlockPosition(const sf::Vector2i &screenPosition) const;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    int m_blockSize;
    sf::Vector2i m_size;
    std::map<int, sf::Texture> m_textures;
    std::vector<sf::RectangleShape> m_backgroundTiles;
};


#endif //RETROLAND_TILEMAP_H
