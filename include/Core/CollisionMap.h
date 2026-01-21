#pragma once
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/System/Vector2.hpp>
#include <stdexcept>

class CollisionMap
{
public:
    CollisionMap(const tmx::Map& map, std::size_t layerIndex);

    bool isSolid(int x, int y) const;

    int getWidth() const;
    int getHeight() const;
    sf::Vector2u getTileSize() const;

private:
    const tmx::TileLayer* m_tileLayer;
    sf::Vector2u m_tileSize;
    int m_widthInTiles;
    int m_heightInTiles;
};

