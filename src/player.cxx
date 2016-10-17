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

// note: the animate method probably can be done in the Character class
void Player::animate() {
    // test block
    // just testing die animation/state - have to finish animation class...
    if(m_animation.getCurrentAnim() == "Die" && 
      m_animation.getFrameRange().x == m_animation.getFrameRange().y) 
    { 
        return; 
    } 
    //m_animation.setLoop(true);
    // end test
    switch(m_action) {
        case Action::None:
            m_dir == Direction::Left ? m_animation.animate("Idle-Left")
              : m_animation.animate("Idle-Right");
            break;
        case Action::Walk:
            m_dir == Direction::Left ? m_animation.animate("Walk-Left")
              : m_animation.animate("Walk-Right");
            break;
        case Action::Jump:
            m_dir == Direction::Left ? m_animation.animate("Jump-Left")
              : m_animation.animate("Jump-Right");
            break;
        case Action::Die:
            m_animation.setLoop(false); // testing
            m_animation.animate("Die");
            break;
    }
}

void Player::update(double updateInterval) {
    Character::update(updateInterval);
    animate();
}