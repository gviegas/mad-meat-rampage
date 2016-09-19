/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef ST_BEGIN_HXX
#define ST_BEGIN_HXX

#include "GameState.h"
#include "InputManager.h"

class STBegin: public cgf::GameState {
public:
    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    static STBegin* instance() { return &m_this; }
protected:
    STBegin() {}
private:
    static STBegin m_this;
    sf::Texture m_texture;
    sf::Sprite m_bg;
    sf::Font m_font;
    sf::Text m_text;
    cgf::InputManager* m_inputs;
};

#endif