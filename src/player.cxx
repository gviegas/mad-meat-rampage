/*
* Created by Gustavo Viegas (2016/09)
*/

#include "player.hxx"

Player::Player(): Character({0, 0}) { // todo: do something with this parameter
    loadConf("data/confs/player.conf");
    m_type = ObjectType::Player;
    m_dir = Direction::Right;
    setPosition({400.0, 400.0}); // testing
}
Player::~Player() {}

void Player::onCollision(Collidable* collidable, Axis axis) {}

void Player::handleInput(const std::string& input) {
    if(input == GameInput::Left) {
        if(m_dir != Direction::Left) { changeDirection(Direction::Left); }
        move(Direction::Left); 
    } else if(input == GameInput::Right) {
        if(m_dir != Direction::Right) { changeDirection(Direction::Right); }
        move(Direction::Right); 
    } else if(input == GameInput::Jump) {
        if(m_action == Action::Jump) { return; }
        m_action = Action::Jump;
        jump(m_impulse);
    }
}