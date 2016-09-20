/*
* Created by Gustavo Viegas (2016/09)
*/

#include "st_game.hxx"

STGame STGame::m_this;

void STGame::init() {}
void STGame::cleanup() {}

void STGame::pause() {}
void STGame::resume() {}

void STGame::handleEvents(cgf::Game* game) {
    sf::RenderWindow* screen = game->getScreen();
    sf::Event event;
    while(screen->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            game->quit();
        }
    }
}

void STGame::update(cgf::Game* game) {}
void STGame::draw(cgf::Game* game) {}