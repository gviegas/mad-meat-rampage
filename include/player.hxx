/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include "character.hxx"

class Player: public Character {
public:
    Player();
    ~Player();

    void onCollision(Collidable* collidable, Axis axis);
    void handleInput(const std::string& input);
    void update(double updateInterval);
};

#endif