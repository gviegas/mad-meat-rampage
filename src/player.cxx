/*
* Created by Gustavo Viegas (2016/09)
*/

#include "player.hxx"
#include "door.hxx" // testing
#include "key.hxx"

Player::Player(sf::Vector2f startPos): Character(startPos) {
    m_type = ObjectType::Player;
    m_dir = Direction::Right;
    m_hasKey = false;
}
Player::~Player() {}

bool Player::hasKey() { return m_hasKey; }

void Player::onCollision(Collidable* collidable, Axis axis) {
    if(collidable->getType() == ObjectType::Trap ||
      collidable->getType() == ObjectType::Enemy) 
    { 
        m_action = Action::Die; 
    } else if(collidable->getType() == ObjectType::Door) {
        // test block
        if(m_hasKey) { std::cout << "good job!" << std::endl; } 
        else { std::cout << "locked!" << std::endl; }
        // end test
    } else if(!m_hasKey && collidable->getType() == ObjectType::Key) {
        ((Key*)collidable)->setUser(this);
        ((Key*)collidable)->setInUse(true);
        m_hasKey = true;
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