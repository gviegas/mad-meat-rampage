/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef COMMON_HXX
#define COMMON_HXX

#include "Game.h"

struct Common {
    Common(): m_game(nullptr) {}
    cgf::Game* m_game;
};

#endif