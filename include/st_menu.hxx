/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef ST_MENU_HXX
#define ST_MENU_HXX

#include "GameState.h"
#include "InputManager.h"

class STMenu: public cgf::GameState {
public:
    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    static STMenu* instance() { return &m_this; }
protected:
    STMenu() {}
private:
    static STMenu m_this;
};

#endif;