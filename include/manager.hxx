/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef MANAGER_HXX
#define MANAGER_HXX

#include "tile_map.hxx"
#include "player.hxx"
#include "InputManager.h"
#include <vector>

// todo: collision handling is in the manager for now
// gotta move out to its on manager class...

enum class CollisionTarget { Tile = 0, Collidable };

struct CollisionData {
    CollisionData(Collidable* collidable, Collidable* other):
      m_collidable(collidable), m_other(other) {}
    CollisionData(Collidable* collidable, sf::FloatRect tileRect):
      m_collidable(collidable), m_tileRect(tileRect) {}
      
    Collidable* m_collidable;
    union {
        sf::FloatRect m_tileRect;
        Collidable* m_other;
    };
};

using Collisions = std::vector<std::pair<CollisionTarget, CollisionData>>;

class Manager {
public:
    Manager();
    ~Manager();

    void init(TileMap* map);
    void handleEvents();
    void update(sf::RenderWindow* screen);
    void draw(sf::RenderWindow* screen);
private:
    bool isColliding(Collidable* collidable, sf::FloatRect tileRect);
    bool isColliding(Collidable* collidA, Collidable* collidB);
    void checkCollisions(Collidable* collidable);
    void resolveCollisions();
    Collisions m_collisions;
    TileMap* m_map;
    Player m_player;
    cgf::InputManager* m_inputs;
};

#endif