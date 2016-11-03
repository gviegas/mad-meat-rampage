/*
* Created by Gustavo Viegas (2016/09)
*/

#include "player.hxx"

Player::Player(): Character({0, 0}) { // todo: do something with this parameter
    loadConf("data/confs/player.conf");
    m_type = ObjectType::Player;
    m_dir = Direction::Right;
    setPosition({448.0, 448.0}); // todo: get start position from map
}
Player::~Player() {}

void Player::onCollision(Collidable* collidable, Axis axis) {
    if(collidable->getType() == ObjectType::Trap ||
      collidable->getType() == ObjectType::Enemy) 
    {
        m_action = Action::Die;
    }
}

void Player::handleInput(const std::string& input) {
    if(m_action == Action::Die) { return; }
    if(input == GameInput::Left) {
        //if(m_action == Action::Jump) { return; }
        if(m_dir != Direction::Left) { changeDirection(); }
        move(Direction::Left); 
    } else if(input == GameInput::Right) {
        //if(m_action == Action::Jump) { return; }
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