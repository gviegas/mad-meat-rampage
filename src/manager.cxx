/*
* Created by Gustavo Viegas (2016/09)
*/

#include "manager.hxx"
#include "st_end.hxx"

Manager::Manager(): m_map(nullptr) {}
Manager::~Manager() {}

void Manager::destroy() {
    delete m_player;
    for(auto& iter : m_objects) { delete iter; }
    m_objects.clear();
    for(auto& iter : m_beings) { delete iter; }
    m_beings.clear();
    m_collidables.clear();
}

void Manager::init(TileMap* map) {
    m_map = map;
    m_ai.createGraph(map);

    m_player = new Player();

    // test block
    GameObject* trap1 = new Trap({540.0, 780.0});
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