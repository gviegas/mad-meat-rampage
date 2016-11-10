/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef TILE_MAP_HXX
#define TILE_MAP_HXX

#include "tile_set.hxx"

class TileMap {
public:
    TileMap();
    ~TileMap();

    sf::FloatRect getTileBBox(const sf::Vector2u& pos); // todo: return ref
    float getGravity() const;
    const sf::Vector2u& getTileSize() const;
    const sf::Vector2u& getGridSize() const;
    bool checkTile(const sf::Vector2u& gridPos);
    void clearTiles();
    
    void loadConf(const std::string& fileName);
    void loadMap(const std::string& fileName);

    void update(double updateInterval);
    void draw(sf::RenderWindow* screen);
private:
    TileSet m_tileSet;
    sf::Texture m_texture;
    sf::Sprite m_bg;
    float m_gravity;
};

#endif