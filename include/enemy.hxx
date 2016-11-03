/*
* Created by Gustavo Viegas (2016/10)
*/

#ifndef ENEMY_HXX
#define ENEMY_HXX

#include "character.hxx"

class Enemy: public Character {
public:
    Enemy();
    ~Enemy();

    void onCollision(Collidable* collidable, Axis axis);
    void update(double updateInterval);
};

#endif