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
    checkCollisions(&m_player);
    resolveCollisions();
}

void Manager::draw(sf::RenderWindow* screen) {
    m_player.draw(screen);
}

bool Manager::isColliding(Collidable* collidable, sf::FloatRect tileRect) {
    return (collidable->getBBox().intersects(tileRect));
}
bool Manager::isColliding(Collidable* collidA, Collidable* collidB) {
    return (collidA->getBBox().intersects(collidB->getBBox()));
}

// todo: check collision between collidables
void Manager::checkCollisions(Collidable* collidable) {
    sf::FloatRect rect = collidable->getBBox();
    int rx = m_map->getTileSize().x;
    int ry = m_map->getTileSize().y;
    for(int x = rect.left / rx; x <= (rect.left + rect.width) / rx; ++x) {
        for(int y = rect.top / ry; y <= (rect.top + rect.height) / ry; ++y) {
            sf::FloatRect tileRect = m_map->getTileBBox({x, y});
            if(isColliding(collidable, tileRect)) {
                CollisionData data {collidable, tileRect};
                m_collisions.emplace_back(std::make_pair(CollisionTarget::Tile, data));
            }
        }
    }
}

void Manager::resolveCollisions() {
    for(auto& iter : m_collisions) {
        if(iter.first == CollisionTarget::Tile) {
            iter.second.m_collidable->onTileCollision(iter.second.m_tileRect);
        } else if(iter.first == CollisionTarget::Collidable) {
            iter.second.m_collidable->onCollision(iter.second.m_other);
        }
    }
    m_collisions.clear();
}