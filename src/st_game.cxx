/*
* Created by Gustavo Viegas (2016/09)
*/

#include "st_game.hxx"

STGame STGame::m_this;

void STGame::init() {
    m_map.loadMap("data/maps/map1.map");
    m_manager.init(&m_map); 
}

void STGame::cleanup() { 
    m_map.clearTiles(); // bg and tile types will be reused
    m_manager.destroy(); 
}

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
    m_manager.handleEvents();
}

void STGame::update(cgf::Game* game) {
    m_map.update(game->getUpdateInterval());
    m_manager.update(game);
}
void STGame::draw(cgf::Game* game) {
    sf::RenderWindow* screen = game->getScreen();
    m_map.draw(screen);
    m_manager.draw(screen);
}