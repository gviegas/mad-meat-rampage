/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef ST_GAME_HXX
#define ST_GAME_HXX

#include "GameState.h"
#include "InputManager.h"
#include "tile_map.hxx"
#include "manager.hxx"

class STGame: public cgf::GameState {
public:
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
};

#endif;