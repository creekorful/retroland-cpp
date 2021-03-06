#include "Inventory.h"

Inventory::Inventory(const sf::Vector2i &screenSize, const std::map<int, sf::Texture> &textures)
{
    // Background solid shape
    m_background.setSize(sf::Vector2f(screenSize.x - 400, screenSize.y - 200));
    m_background.setPosition(0 + 200, 0 + 100);
    m_background.setFillColor(sf::Color(52, 73, 94, 240));

    // Create items
    int x = 0, y = 0, i = 0;
    for (const auto&[textureId, texture] : textures) {
        sf::RectangleShape item(sf::Vector2f(150, 150));

        // Line return if x is > than background width
        if (100 + (x * 150 * 2) + item.getSize().x > m_background.getSize().x) {
            x = 0;
            y++;
        }

        sf::Vector2f itemPos(m_background.getPosition().x + 100 + (x * 150 * 2),
                             m_background.getPosition().y + 100 + (y * 150 * 2));
        item.setPosition(itemPos);
        item.setFillColor(sf::Color::White);
        item.setTexture(&texture);
        m_items.push_back(item);
        m_tiles[i] = textureId;
        x++;
        i++;
    }
}

int Inventory::getTileId(const sf::Vector2f &worldPos)
{
    for (int i = 0; i < m_items.size(); i++) {
        if (m_items[i].getGlobalBounds().contains(worldPos)) {
            return m_tiles[i];
        }
    }

    return -1;
}

void Inventory::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_background, states);

    for (const auto &item : m_items) {
        target.draw(item, states);
    }
}
