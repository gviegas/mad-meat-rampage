/*
* Created by Gustavo Viegas (2016/09)
*/

#include "player.hxx"
#include "door.hxx"
#include "key.hxx"
#include "audio_manager.hxx"

Player::Player(sf::Vector2f startPos): Character(startPos) {
    m_type = ObjectType::Player;
    m_dir = Direction::Right;
    m_levelCompleted = false;
    m_hasKey = false;
}
Player::~Player() {}


bool Player::levelCompleted() { return m_levelCompleted; }
bool Player::hasKey() { return m_hasKey; }

void Player::onCollision(Collidable* collidable, Axis axis) {
    if(m_action == Action::Die) { return; }
    if(collidable->getType() == ObjectType::Trap ||
      collidable->getType() == ObjectType::Enemy) 
    { 
        m_action = Action::Die; 
        AudioManager::instance()->playSound("Death");
    } else if(collidable->getType() == ObjectType::Door) {
        if(m_hasKey) { 
            m_levelCompleted = true; 
            AudioManager::instance()->playSound("Door");
        }
        else { std::cout << "locked!" << std::endl; } // what about printing this messsage in front of the door? Or play a locked sound perhaps?
    } else if(!m_hasKey && collidable->getType() == ObjectType::Key) {
        ((Key*)collidable)->setUser(this);
        ((Key*)collidable)->setInUse(true);
        m_hasKey = true;
        AudioManager::instance()->playSound("Key");
    }
}

void Player::handleInput(const std::string& input) {
    if(m_action == Action::Die) { return; }
    if(input == GameInput::Left) {
        if(m_dir != Direction::Left) { changeDirection(); }
        move(Direction::Left); 
    } else if(input == GameInput::Right) {
        if(m_dir != Direction::Right) { changeDirection(); }
        move(Direction::Right); 
    } else if(input == GameInput::Jump) {
        if(m_action == Action::Jump) { return; }
        m_action = Action::Jump;
        jump(m_impulse);
    }
}

void Player::update(double updateInterval) {
    Character::update(updateInterval);
}