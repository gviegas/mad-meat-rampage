/*
* Created by Gustavo Viegas (2016/11)
*/

#ifndef DOOR_HXX
#define DOOR_HXX

#include "game_object.hxx" 

class Door: public GameObject {
public:
    Door(sf::Vector2f fixedPos);
    ~Door();

    void loadConf(const std::string& fileName);

    void onTileCollision(sf::FloatRect tileRect, Axis axis);
    void onCollision(Collidable* collidable, Axis axis);

    void setWarp(bool warp);
    bool isWarp();

    void update(double updateInterval);
    void draw(sf::RenderWindow* screen);
private:
    // could have a reference here for the next level
    bool m_warp; // can be a fake door
};

#endif