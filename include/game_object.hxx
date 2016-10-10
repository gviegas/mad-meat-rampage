/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef GAME_OBJECT_HXX
#define GAME_OBJECT_HXX

#include "drawable.hxx"
#include "collidable.hxx"

class GameObject: public Drawable, public Collidable {
public:
    GameObject(sf::Vector2f fixedPos) { m_fixedPos = fixedPos; }
    virtual ~GameObject() {}

    virtual void update(double updateInterval) = 0;
protected:
    sf::Vector2f m_fixedPos;
};

#endif