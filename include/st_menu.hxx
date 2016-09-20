/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef ST_MENU_HXX
#define ST_MENU_HXX

#include "GameState.h"
#include "InputManager.h"
#include "aux.hxx"
#include <unordered_map>

enum class ButtonType { Play = 0, Options, Credits, Exit, Continue };
using Buttons = std::unordered_map<ButtonType, sf::Sprite, aux::Hasher>;

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

    void loadConf(const std::string& fileName);
protected:
    STMenu() {}
private:
    static STMenu m_this;
    sf::Texture m_texture;
    Buttons m_buttons;
    cgf::InputManager* m_inputs;
};

#endif;