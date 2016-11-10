/*
* Created by Gustavo Viegas (2016/11)
*/

#ifndef KEY_HXX
#define KEY_HXX

#include "usable.hxx"

class Key: public Usable {
public:
    Key(sf::Vector2f startPos);
    ~Key();

    void animate();
    void onCollision(Collidable* collidable, Axis axis);
};

#endif