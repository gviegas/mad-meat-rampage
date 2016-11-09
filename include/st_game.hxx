/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef ST_GAME_HXX
#define ST_GAME_HXX

#include "GameState.h"
#include "InputManager.h"
#include "tile_map.hxx"
#include "manager.hxx"

using GameConfig = std::vector<std::pair<std::string, std::string>>;

class STGame: public cgf::GameState {
public:
    void setup(const std::string& fileName);
    void toNextLevel();

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    static STGame* instance() { return &m_this; }
protected:
    STGame() {}
private:
    static STGame m_this;
    TileMap m_map;
    Manager m_manager;
    bool m_setupDone = false;
    GameConfig m_config;
    unsigned int m_nextLevel = 0;
};

#endif