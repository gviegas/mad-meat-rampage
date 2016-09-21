/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef TILE_SET_HH
#define TILE_SET_HH

#include <SFML/Graphics.hpp>
#include <unordered_map>

struct TileType {
    TileType(sf::IntRect rect) { m_sprite.setTextureRect(rect); }
    sf::Sprite m_sprite;
};

struct Tile {
    Tile(TileType* type, sf::Vector2u pos): 
      m_type(type), m_pos(pos) {}
    sf::Vector2u m_pos;
    TileType* m_type;
};

using TileTypeId = unsigned int;
using TilePos = unsigned int;
using TileTypes = std::unordered_map<TileTypeId, TileType*>;
using Tiles = std::unordered_map<TilePos, Tile*>;

class TileSet {
public:
    TileSet(sf::Vector2u gridSize);
    ~TileSet();

    Tile* getTile(const sf::Vector2u& pos);
    Tiles* getTileSet();
    void setTexture(const std::string& texFile);

    bool addTileType(TileTypeId id, TileType* type);
    bool removeTileType(TileTypeId id);
    void clearTileTypes();

    bool addTile(TileTypeId id, sf::Vector2u pos);
    bool removeTile(TilePos id);
    void clearTiles();
private:
    TilePos toSingleCoordPos(const sf::Vector2u& pos);
    TileTypes m_types;
    Tiles m_tiles;
    sf::Texture m_texture;
    sf::Vector2u m_gridSize;
};

#endif