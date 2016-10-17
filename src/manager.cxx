/*
* Created by Gustavo Viegas (2016/09)
*/

#include "manager.hxx"

Manager::Manager(): m_map(nullptr) {}
Manager::~Manager() {
    for(auto& iter : m_objects) { delete iter; }
    m_objects.clear();
    for(auto& iter : m_beings) { delete iter; }
    m_beings.clear();
    m_collidables.clear();
}

void Manager::init(TileMap* map) {
    m_map = map;

    // test block
    GameObject* trap1 = new Trap({160.0, 580.0});
    ((Trap*)trap1)->loadConf("data/confs/trap1.conf");
    m_objects.emplace_back(trap1);
    m_collidables.emplace_back(trap1);

    GameBeing* enemy = new Enemy();
    //((Enemy*)enemy)->loadConf("data/confs/enemy1.conf");
    m_beings.emplace_back(enemy);
    m_collidables.emplace_back(enemy);
    // end test

    m_inputs = cgf::InputManager::instance();
    m_inputs->addKeyInput(GameInput::Left, sf::Keyboard::Left);
    m_inputs->addKeyInput(GameInput::Right, sf::Keyboard::Right);
    m_inputs->addKeyInput(GameInput::Jump, sf::Keyboard::Up);
}

void Manager::handleEvents() {
    if(m_inputs->testEvent(GameInput::Left)) { 
        m_player.handleInput(GameInput::Left); 
    }
    if(m_inputs->testEvent(GameInput::Right)) {
        m_player.handleInput(GameInput::Right);
    }
    if(m_inputs->testEvent(GameInput::Jump)) {
        m_player.handleInput(GameInput::Jump);
    }
}

void Manager::update(double updateInterval) {
    for(auto& iter : m_objects) { iter->update(updateInterval); }
    for(auto& iter : m_beings) { iter->update(updateInterval); }
    m_player.update(updateInterval);

    // no collision check for traps...
    for(auto& iter : m_beings) { 
        m_collisionSystem.checkCollisions(iter, m_collidables, m_map);
    }
    m_collisionSystem.checkCollisions(&m_player, m_collidables, m_map);
    m_collisionSystem.resolveCollisions();
}

void Manager::draw(sf::RenderWindow* screen) {
    for(auto& iter : m_objects) { iter->draw(screen); }
    for(auto& iter : m_beings) { iter->draw(screen); }
    m_player.draw(screen);
}