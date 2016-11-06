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
#include "ai.hxx"
#include "ui.hxx"
#include "GameState.h"
#include "InputManager.h"

using EntityTextures = std::unordered_map<std::string, sf::Texture>;
using ObjectTemplates = std::unordered_map<std::string, GameObject*>;
using BeingTemplates = std::unordered_map<std::string, GameBeing*>;
using GameObjects = std::vector<GameObject*>;
using GameBeings = std::vector<GameBeing*>;

class Manager {
public:
    Manager();
    ~Manager();

    void init(TileMap* map);
    void destroy();

    void loadConf(const std::string& fileName);
    void loadEntities(const std::string& fileName);

    void handleEvents();
    void update(cgf::Game* game);
    void draw(sf::RenderWindow* screen);
private:
    EntityTextures m_textures;
    ObjectTemplates m_objectTem;
    BeingTemplates m_beingTem;
    TileMap* m_map;
    Player* m_player;
    GameObjects m_objects;
    GameBeings m_beings;
    Collidables m_collidables;
    CollisionSystem m_collisionSystem;
    AI m_ai;
    UI m_ui;
    int m_score;
    cgf::InputManager* m_inputs;
};

#endif