#include "Inventory.h"

Inventory::Inventory(const sf::Vector2i &screenSize, const std::map<int, sf::Texture> &textures)
{
    // Background solid shape
    m_background.setSize(sf::Vector2f(screenSize.x - 400, screenSize.y - 200));
    m_background.setPosition(0 + 200, 0 + 100);
    m_background.setFillColor(sf::Color(52, 73, 94, 240));

    // Create items
    int i = 0;
    for (const auto&[id, texture] : textures) {
        sf::RectangleShape item(sf::Vector2f(150, 150));
        item.setPosition(m_background.getPosition().x + 100 + (i * 150 * 2), m_background.getPosition().y + 100);
        item.setFillColor(sf::Color::White);
        item.setTexture(&texture);
        m_items.push_back(item);
        i++;
    }
}

void Inventory::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_background, states);

    for (const auto &item : m_items) {
        target.draw(item, states);
    }
}
