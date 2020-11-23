#ifndef RETROLAND_TILEMAPRENDERER_H
#define RETROLAND_TILEMAPRENDERER_H

#include <SFML/Graphics.hpp>

#include "TileMap.h"

class TileMapRenderer : public sf::Drawable
{
public:
    // TODO: do not use copy constructor for textures?
    TileMapRenderer(const TileMap &tileMap, const sf::Vector2i &screenSize, const std::map<int, sf::Texture> &textures);

    void update(const TileMap &tileMap);

    void toggleGrid();

    sf::Vector2i getTilePosition(const sf::Vector2f &worldPos) const;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    bool m_showGrid;
    int m_tileSize;
    std::map<int, sf::Texture> m_textures;
    std::map<int, std::vector<sf::RectangleShape>> m_tileDrawables;
};


#endif //RETROLAND_TILEMAPRENDERER_H
