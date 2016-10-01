/*
* Created by Gustavo Viegas (2016/09)
*/

#include "manager.hxx"

Manager::Manager(): m_map(nullptr) {}
Manager::~Manager() {}

void Manager::init(TileMap* map) {
    m_map = map;

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

void Manager::update(sf::RenderWindow* screen) {
    m_player.update(screen);
    m_collisionSystem.checkCollisions(&m_player, m_collidables, m_map);
    m_collisionSystem.resolveCollisions();
}

void Manager::draw(sf::RenderWindow* screen) {
    m_player.draw(screen);
}