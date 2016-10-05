/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef CHARACTER_HXX
#define CHARACTER_HXX

#include "game_being.hxx"

class Character: public GameBeing {
public:
    Character(sf::Vector2f startPos);
    virtual ~Character();

    void loadConf(const std::string& fileName);

    void onTileCollision(sf::FloatRect tileRect, Axis axis);
    virtual void onCollision(Collidable* collidable, Axis axis) = 0;

    void update(double updateInterval);
    void draw(sf::RenderWindow* screen);
};

#endif