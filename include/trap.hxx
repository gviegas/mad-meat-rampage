/*
* Created by Gustavo Viegas (2016/10)
*/

#ifndef TRAP_HXX
#define TRAP_HXX

#include "game_object.hxx"

#include "animation.hxx"

class Trap: public GameObject {
public:
    Trap(sf::Vector2f fixedPos);
    ~Trap();

    void loadConf(const std::string& fileName);

    void onTileCollision(sf::FloatRect tileRect, Axis axis);
    void onCollision(Collidable* collidable, Axis axis);

    void update(double updateInterval);
    void draw(sf::RenderWindow* screen);
private:
    Animation m_animation;
};

#endif