/*
* Created by Gustavo Viegas (2016/09)
*/

#include "st_game.hxx"
#include "aux.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

STGame STGame::m_this;

void STGame::setup(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: STGame::setup - " << fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "LEVEL") {
                std::string mapFile, entitiesFile;
                sstream >> mapFile >> entitiesFile;
                m_config.emplace_back(std::make_pair(mapFile, entitiesFile));
            }
        }
        file.close();
    }
}

void STGame::toNextLevel() { ++m_nextLevel; }

void STGame::init() {
    //m_map.loadMap("data/maps/map1.map");
    //m_manager.init(&m_map);
    if(!m_setupDone) {
        setup("data/game.setup");
        m_setupDone = true;
    }
    m_nextLevel %= m_config.size();
    m_map.loadMap(m_config[m_nextLevel].first);
    m_manager.init(m_config[m_nextLevel].second, &m_map);
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