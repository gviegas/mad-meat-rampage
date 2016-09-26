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

    void onTileCollision(sf::FloatRect tileRect);
    virtual void onCollision(Collidable* collidable) = 0;

    void update(sf::RenderWindow* screen);
    void draw(sf::RenderWindow* screen);
};

#endif