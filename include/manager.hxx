/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef MANAGER_HXX
#define MANAGER_HXX

#include "tile_map.hxx"
#include "player.hxx"
#include "trap.hxx"
#include "enemy.hxx"
#include "collision_system.hxx"
#include "InputManager.h"

using GameObjects = std::vector<GameObject*>;
using GameBeings = std::vector<GameBeing*>;

class Manager {
public:
    Manager();
    ~Manager();

    void init(TileMap* map);
    void handleEvents();
    void update(double updateInterval);
    void draw(sf::RenderWindow* screen);
private:
    TileMap* m_map;
    Player m_player;
    GameObjects m_objects;
    GameBeings m_beings;
    Collidables m_collidables;
    CollisionSystem m_collisionSystem;
    cgf::InputManager* m_inputs;
};

#endif