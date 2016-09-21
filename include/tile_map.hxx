/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef TILE_MAP_HH
#define TILE_MAP_HH

#include "tile_set.hxx"

class TileMap {
public:
    TileMap();
    ~TileMap();

    sf::FloatRect getTileBB(const sf::Vector2u& pos);
    sf::Vector2f getPlayerStart() const;
    float getGravity() const;

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