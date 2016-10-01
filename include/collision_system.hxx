/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef COLLISION_SYSTEM_HXX
#define COLLISION_SYSTEM_HXX

#include "collidable.hxx"
#include "tile_map.hxx"
#include <vector>

enum class CollisionTarget { Tile = 0, Collidable };

struct CollisionData {
    CollisionData(Collidable* collidable, Collidable* other, Axis axis):
      m_collidable(collidable), m_other(other), m_axis(axis) {}
    CollisionData(Collidable* collidable, sf::FloatRect tileRect, Axis axis):
      m_collidable(collidable), m_tileRect(tileRect), m_axis(axis) {}
    
    Collidable* m_collidable;
    Axis m_axis;
    union {
        sf::FloatRect m_tileRect;
        Collidable* m_other;
    };
};

using Collisions = std::vector<std::pair<CollisionTarget, CollisionData>>;
using Collidables = std::vector<Collidable*>;

class CollisionSystem {
public:
    CollisionSystem();
    ~CollisionSystem();

    void checkCollisions(Collidable* collidable, 
      Collidables& collidables, TileMap* map);
    void resolveCollisions();
private:
    bool isColliding(Collidable* collidable, sf::FloatRect tileRect,
      sf::FloatRect& intersection);
    bool isColliding(Collidable* collidA, Collidable* collidB,
      sf::FloatRect& intersection);
    Axis getCollisionAxis(sf::FloatRect& intersection);
    void checkTileCollisions(Collidable* collidable, TileMap* map);
    void checkCollidableCollisions(Collidable* collidable, 
      Collidables& collidables);

    Collisions m_collisions;
};

#endif