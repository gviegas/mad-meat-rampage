/*
* Created by Gustavo Viegas (2016/10)
*/

#include "enemy.hxx"
#include <ctime>

Enemy::Enemy(): Character({0, 0}) { // todo: do something with this parameter
    loadConf("data/confs/enemy1.conf");
    m_type = ObjectType::Enemy;
    m_dir = Direction::Left;
    setPosition({1000, 400}); // todo: make the start pos random perhaps?
    srand(time(NULL));
}
Enemy::~Enemy() {}

void Enemy::onCollision(Collidable* collidable, Axis axis) {
    if(collidable->getType() == ObjectType::Trap) {
        m_action = Action::Die;
    }
}

// note: the animate method probably can be done in the Character class
void Enemy::animate() {
    // test block
    if(m_animation.getCurrentAnim() == "Die" && 
      m_animation.getFrameRange().x == m_animation.getFrameRange().y)
    {
        return;
    }
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
            m_animation.setLoop(false);
            m_animation.animate("Die");
            break;
    }
}

void Enemy::update(double updateInterval) {
    Character::update(updateInterval);
    animate();
    
    // test block
    //std::cout << "pos: " << m_pos.x << " " << m_pos.y <<
    //  " old: " << m_oldPos.x << " " << m_oldPos.y << std::endl;
    if(m_oldPos == m_pos) {
        int rnd = rand();
        if(rnd % 2) {
            if(m_action != Action::Jump) {
                m_action = Action::Jump;
                jump(m_impulse); 
            }
        } else { changeDirection(); }
    }
    if(m_dir == Direction::Left) {
        if(m_pos.x < 128) {
            m_dir = Direction::Right;
            move(Direction::Right);
        } else {
            move(Direction::Left);
        }
    } else if(m_dir == Direction::Right) {
        if(m_pos.x > 1152) {
            m_dir = Direction::Left;
            move(Direction::Left);
        } else {
            move(Direction::Right);
        }
    }
    // std::cout << "x: " << m_pos.x << " y: " << m_pos.y << " dir: " << (int)m_dir << std::endl;
    // end test
}