#ifndef RETROLAND_INVENTORY_H
#define RETROLAND_INVENTORY_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class Inventory : public sf::Drawable
{
public:
    Inventory(const sf::Vector2i &screenSize, const std::map<int, sf::Texture> &textures);

    int getTileId(const sf::Vector2f &worldPos);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::RectangleShape m_background;
    std::vector<sf::RectangleShape> m_items;

    // TODO better lookup
    std::map<int, int> m_tiles;
};


#endif //RETROLAND_INVENTORY_H
