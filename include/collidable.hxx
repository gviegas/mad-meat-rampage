/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef COLLIDABLE_HXX
#define COLLIDABLE_HXX

#include "definitions.hxx"
#include "tile_map.hxx"
#include <SFML/Graphics.hpp>

class Collidable {
public:
    Collidable() {}
    virtual ~Collidable() {}

    const sf::FloatRect& getBBox() const { return m_bBox; }
    const ObjectType& getType() const { return m_type; }

    virtual void onTileCollision(sf::FloatRect tileRect) = 0;
    virtual void onCollision(Collidable* collidable) = 0;
protected:
    sf::FloatRect m_bBox;
    ObjectType m_type;
};

#endif