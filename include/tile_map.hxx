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
    const sf::Vector2f& getPlayerStart() const;
    float getGravity() const;
    const sf::Vector2u& getTileSize() const;

    void loadConf(const std::string& fileName);
    void loadMap(const std::string& fileName);

    void update(sf::RenderWindow* screen);
    void draw(sf::RenderWindow* screen);
private:
    TileSet m_tileSet;
    sf::Texture m_texture;
    sf::Sprite m_bg;
    sf::Vector2f m_playerStart;
    float m_gravity;
};

#endif