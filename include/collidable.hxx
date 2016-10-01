/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef COLLIDABLE_HXX
#define COLLIDABLE_HXX

#include "definitions.hxx"
#include "tile_map.hxx"
#include <SFML/Graphics.hpp>

enum class Axis { X = 0, Y };

class Collidable {
public:
    Collidable() {}
    virtual ~Collidable() {}

    const sf::FloatRect& getBBox() const { return m_bBox; }
    const ObjectType& getType() const { return m_type; }

    virtual void onTileCollision(sf::FloatRect tileRect, Axis axis) = 0;
    virtual void onCollision(Collidable* collidable, Axis axis) = 0;
protected:
    sf::FloatRect m_bBox;
    ObjectType m_type;
};

#endif