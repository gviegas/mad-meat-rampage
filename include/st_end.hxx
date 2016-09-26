/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef ST_END_HXX
#define ST_END_HXX

#include "GameState.h"
#include "InputManager.h"

class STEnd: public cgf::GameState {
public:
    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    static STEnd* instance() { return &m_this; }
protected:
    STEnd() {}
private:
    static STEnd m_this;
};

#endif;