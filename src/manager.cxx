/*
* Created by Gustavo Viegas (2016/09)
*/

#include "manager.hxx"
#include "st_end.hxx"
#include "aux.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

Manager::Manager(): m_map(nullptr), m_player(nullptr) {}
Manager::~Manager() {}

void Manager::destroy() {
    for(auto& iter : m_objects) { delete iter; }
    m_objects.clear();
    for(auto& iter : m_beings) { delete iter; }
    m_beings.clear();
    m_collidables.clear();
    
    // What about create & destroy this only once?
    for(auto& iter : m_objectTem) { delete iter.second; }
    m_objectTem.clear();
    for(auto& iter : m_beingTem) { delete iter.second; }
    m_beingTem.clear();
}

// DOING block
void Manager::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: Manager::loadConf - " << fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            // if(attr == "TEXTURE") {
            //     std::string texName, texPath;
            //     sstream >> texName >> texPath;
            //     auto iter = m_textures.find(texName);
            //     if(iter == m_textures.end()) {
            //         std::cerr << "ERROR: Manager::loadconf - texture " <<
            //           texName << " already exists" << std::endl;
            //     } else {
            //         m_textures.emplace(texName, sf::Texture()).first->
            //           second.loadFromFile(aux::getBasePath() + texPath);
            //     }
            // } else if(attr == "PLAYER") {
            if(attr == "PLAYER") {
                std::string name, confPath;
                sstream >> name >> confPath;
                m_player = new Player({0, 0});
                m_player->loadConf(confPath);
                m_beingTem.emplace(name, m_player);
            } else if(attr == "ENEMY") {
                std::string name, confPath;
                sstream >> name >> confPath;
                Enemy* enemy = new Enemy({0, 0});
                enemy->loadConf(confPath);
                m_beingTem.emplace(name, enemy);
            } else if(attr == "TRAP") {
                std::string name, confPath;
                sstream >> name >> confPath;
                Trap* trap = new Trap({0, 0});
                trap->loadConf(confPath);
                m_objectTem.emplace(name, trap);
            } else if(attr == "DOOR") {
                std::string name, confPath;
                sstream >> name >> confPath;
                // todo
            } else if(attr == "KEY") {
                std::string name, confPath;
                sstream >> name >> confPath;
                // todo
            }
        }
        file.close();
    }
}

void Manager::loadEntities(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: Manager::loadEntities - " 
          << fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "PLAYER") {
                std::string name; // ignoring this for now
                float x, y;
                sstream >> name >> x >> y;
                m_player->setPosition({x, y});
            } else if(attr == "ENEMY") {
                std::string name;
                float x, y;
                sstream >> name >> x >> y;
                auto iter = m_beingTem.find(name);
                if(iter == m_beingTem.end()) {
                    std::cerr << "ERROR: Manager::loadEntities - " <<
                      name << " template does not exist" << std::endl;
                } else {
                    Enemy* enemy = new Enemy(*(Enemy*)(iter->second));
                    enemy->getAnimation().setSprite(enemy->getSprite()); // testing - this should be made by default
                    m_beings.emplace_back(enemy);
                    m_collidables.emplace_back(enemy);
                }
            } else if(attr == "TRAP") {
                std::string name;
                float x, y;
                sstream >> name >> x >> y;
                // todo
            } else if(attr == "DOOR") {
                std::string name;
                float x, y;
                sstream >> name >> x >> y;
                // todo
            } else if(attr == "KEY") {
                std::string name;
                float x, y;
                sstream >> name >> x >> y;
                // todo
            }
        }
        file.close();
    }
}
// end DOING

void Manager::init(TileMap* map) {
    loadConf("data/confs/manager.conf");
    loadEntities("data/entities/entities.ent");
    
    m_map = map;
    m_ai.createGraph(map);

    // // test block
    // m_player = new Player({448.0, 448.0});
    // Player* p2 = new Player(*m_player);

    // GameObject* trap1 = new Trap({540.0, 780.0});
    // m_objects.emplace_back(trap1);
    // m_collidables.emplace_back(trap1);

    // GameBeing* enemy = new Enemy({940.0, 448.0});
    // m_beings.emplace_back(enemy);
    // m_collidables.emplace_back(enemy);
    // // end test

    m_inputs = cgf::InputManager::instance();
    m_inputs->addKeyInput(GameInput::Left, sf::Keyboard::Left);
    m_inputs->addKeyInput(GameInput::Right, sf::Keyboard::Right);
    m_inputs->addKeyInput(GameInput::Jump, sf::Keyboard::Up);
}

void Manager::handleEvents() {
    if(m_inputs->testEvent(GameInput::Left)) { 
        m_player->handleInput(GameInput::Left); 
    }
    if(m_inputs->testEvent(GameInput::Right)) {
        m_player->handleInput(GameInput::Right);
    }
    if(m_inputs->testEvent(GameInput::Jump)) {
        m_player->handleInput(GameInput::Jump);
    }
}

void Manager::update(cgf::Game* game) {
    double updateInterval = game->getUpdateInterval();
    
    // checking removals
    if(m_player->toRemove()) {
        game->changeState(STEnd::instance());
        return;
    }
    for(auto iter = m_beings.begin(); iter != m_beings.end(); ++iter) {
        if(((Character*)(*iter))->toRemove()) {
            // bad choice of container...
            for(auto iter2 = m_collidables.begin(); 
              iter2 != m_collidables.end(); ++iter2)
            {
                if(*iter2 == *iter) {
                    delete *iter;
                    m_collidables.erase(iter2);
                    m_beings.erase(iter);
                    break;
                }
            }
            break;
        }
    }

    // updating entities
    for(auto& iter : m_objects) { iter->update(updateInterval); }
    for(auto& iter : m_beings) { iter->update(updateInterval); }
    m_player->update(updateInterval);

    // processing collisions
    for(auto& iter : m_beings) { 
        m_collisionSystem.checkCollisions(iter, m_collidables, m_map);
    }
    m_collisionSystem.checkCollisions(m_player, m_collidables, m_map);
    m_collisionSystem.resolveCollisions();

    // finding paths
    for(auto& iter : m_beings) {
        m_ai.act((Character*)iter, m_player);
    }
}

void Manager::draw(sf::RenderWindow* screen) {
    for(auto& iter : m_objects) { iter->draw(screen); }
    for(auto& iter : m_beings) { iter->draw(screen); }
    m_player->draw(screen);
}