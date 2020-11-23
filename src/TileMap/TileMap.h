#ifndef RETROLAND_TILEMAP_H
#define RETROLAND_TILEMAP_H

#include <vector>
#include <fstream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Network/Packet.hpp>

class TileMap
{
public:
    // Create a new empty tilemap
    TileMap();

    // Create brand new tilemap of given size
    explicit TileMap(const sf::Vector2i &size);

    // Load a tilemap from save file
    explicit TileMap(std::ifstream &file);

    void setBackgroundTile(const sf::Vector2i &pos, int tileId);

    void setForegroundTile(const sf::Vector2i &pos, int tileId);

    void setTile(const sf::Vector2i &pos, int layer, int tileId);

    int getTile(const sf::Vector2i &pos, int layer) const;

    bool save(std::ofstream &file) const;

    sf::Vector2i size() const;

    friend sf::Packet &operator<<(sf::Packet &packet, const TileMap &tileMap);

    friend sf::Packet &operator>>(sf::Packet &packet, TileMap &tileMap);

private:
    sf::Vector2i m_size;
    std::map<int, std::vector<int>> m_tileIds;
};

#endif //RETROLAND_TILEMAP_H
