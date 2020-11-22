#ifndef RETROLAND_TILEMAP_H
#define RETROLAND_TILEMAP_H

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable
{
public:
    TileMap(sf::Vector2i size);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
};


#endif //RETROLAND_TILEMAP_H
