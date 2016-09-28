/*
* Created by Gustavo Viegas (2016/09)
*/

#include "player.hxx"

Player::Player(): Character({0, 0}) { // todo: do something with this parameter
    loadConf("data/confs/player.conf");
    m_type = ObjectType::Player;
    m_dir = Direction::Right;
    setPosition({340.0, 0.0}); // testing
}
Player::~Player() {}

void Player::onCollision(Collidable* collidable) {}

void Player::handleInput(const std::string& input) {
    if(input == GameInput::Left) {
        if(m_dir != Direction::Left) { changeDirection(Direction::Left); }
        move(Direction::Left); 
    } else if(input == GameInput::Right) {
        if(m_dir != Direction::Right) { changeDirection(Direction::Right); }
        move(Direction::Right); 
    } else if(input == GameInput::Jump) {
        //if(m_condition == Condition::Jumping) { return; }
        m_condition = Condition::Jumping;
        jump(m_jumpHeight); // testing
    }
}