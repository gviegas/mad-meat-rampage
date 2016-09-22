/*
* Created by Gustavo Viegas (2016/09)
*/

#include "tile_set.hxx"
#include "aux.hxx"
#include <iostream>

TileSet::TileSet(sf::Vector2u gridSize, sf::Vector2u tileSize): 
  m_gridSize(gridSize), m_tileSize(tileSize) {}

TileSet::~TileSet() {
    clearTileTypes();
    clearTiles();
}

Tile* TileSet::getTile(const sf::Vector2u& pos) {
    auto iter = m_tiles.find(toSingleCoordPos(pos));
    return (iter == m_tiles.end() ? nullptr : iter->second);
}

Tiles* TileSet::getTileSet() { return &m_tiles; }
sf::Vector2u TileSet::getGridSize() { return m_gridSize; }
sf::Vector2u TileSet::getTileSize() { return m_tileSize; }

void TileSet::setTexture(const std::string& texFile) {
    m_texture.loadFromFile(aux::getBasePath() + texFile);
}

bool TileSet::addTileType(TileTypeId id, TileType* type) { 
    type->m_sprite.setTexture(m_texture);
    return (m_types.emplace(id, type).second);
}

bool TileSet::removeTileType(TileTypeId id) {
    auto iter = m_types.find(id);
    if(iter == m_types.end()) { return false; }
    delete iter->second;
    return (m_types.erase(id) ? true : false);
}

void TileSet::clearTileTypes() {
    for(auto& iter : m_types) { delete iter.second; }
    m_types.clear();
}

bool TileSet::addTile(TileTypeId id, sf::Vector2u pos) {
    auto iter = m_types.find(id);
    if(iter == m_types.end()) { return false; }
    Tile* tile = new Tile(iter->second, pos);
    return (m_tiles.emplace(toSingleCoordPos(pos), tile).second);
}

bool TileSet::removeTile(TilePos pos) {
    auto iter = m_tiles.find(pos);
    if(iter == m_tiles.end()) { return false; }
    delete iter->second;
    return (m_tiles.erase(pos) ? true : false);
}

void TileSet::clearTiles() {
    for(auto& iter : m_tiles) { delete iter.second; }
    m_tiles.clear();
}

TilePos TileSet::toSingleCoordPos(const sf::Vector2u& pos) {
    return ((pos.x * m_gridSize.x) + pos.y);
}