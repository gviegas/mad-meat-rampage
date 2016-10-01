/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef MANAGER_HXX
#define MANAGER_HXX

#include "tile_map.hxx"
#include "player.hxx"
#include "collision_system.hxx"
#include "InputManager.h"

class Manager {
public:
    Manager();
    ~Manager();

    void init(TileMap* map);
    void handleEvents();
    void update(sf::RenderWindow* screen);
    void draw(sf::RenderWindow* screen);
private:
    TileMap* m_map;
    Player m_player;
    Collidables m_collidables;
    CollisionSystem m_collisionSystem;
    cgf::InputManager* m_inputs;
};

#endif