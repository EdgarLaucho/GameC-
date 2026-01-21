#include <Core/CollisionMap.h>

CollisionMap::CollisionMap(const tmx::Map& map, std::size_t layerIndex)
{
    const auto& layers = map.getLayers();
    if (layerIndex >= layers.size() || layers[layerIndex]->getType() != tmx::Layer::Type::Tile)
        throw std::runtime_error("Layer no válida para colisión");

    m_tileLayer = &layers[layerIndex]->getLayerAs<tmx::TileLayer>();

    auto size = map.getTileSize();
    m_tileSize = sf::Vector2u(size.x, size.y); // convertimos tmx::Vector2u a sf::Vector2u

    auto bounds = map.getBounds();
    m_widthInTiles = bounds.width / m_tileSize.x;
    m_heightInTiles = bounds.height / m_tileSize.y;
}

bool CollisionMap::isSolid(int x, int y) const
{
    if (x < 0 || y < 0 || x >= m_widthInTiles || y >= m_heightInTiles) return false;

    // Cada TileLayer tiene m_tiles vector privado, pero podemos usar getTiles() que devuelve el vector
    auto& tiles = m_tileLayer->getTiles();
    int index = y * m_widthInTiles + x;
    if (index < 0 || index >= static_cast<int>(tiles.size())) return false;

    return tiles[index].ID != 0;
}

int CollisionMap::getWidth() const { return m_widthInTiles; }
int CollisionMap::getHeight() const { return m_heightInTiles; }
sf::Vector2u CollisionMap::getTileSize() const { return m_tileSize; }

