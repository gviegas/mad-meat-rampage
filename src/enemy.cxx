/*
* Created by Gustavo Viegas (2016/10)
*/

#include "enemy.hxx"
#include <ctime>

Enemy::Enemy(): Character({0, 0}) { // todo: do something with this parameter
    loadConf("data/confs/enemy1.conf");
    m_type = ObjectType::Enemy;
    m_dir = Direction::Left;
    setPosition({940, 400}); // todo: make the start pos random perhaps?    
    srand(time(NULL));
}
Enemy::~Enemy() {}

void Enemy::onCollision(Collidable* collidable, Axis axis) {
    if(collidable->getType() == ObjectType::Trap) {
        m_action = Action::Die;
    }
}

void Enemy::update(double updateInterval) {
    Character::update(updateInterval);
    
    // // test block
    // //std::cout << "pos: " << m_pos.x << " " << m_pos.y <<
    // //  " old: " << m_oldPos.x << " " << m_oldPos.y << std::endl;
    // if(m_oldPos == m_pos) {
    //     int rnd = rand();
    //     if(rnd % 2) {
    //         if(m_action != Action::Jump) {
    //             m_action = Action::Jump;
    //             jump(m_impulse); 
    //         }
    //     } else { changeDirection(); }
    // }
    // if(m_dir == Direction::Left) {
    //     if(m_pos.x < 128) {
    //         m_dir = Direction::Right;
    //         move(Direction::Right);
    //     } else {
    //         move(Direction::Left);
    //     }
    // } else if(m_dir == Direction::Right) {
    //     if(m_pos.x > 1152) {
    //         m_dir = Direction::Left;
    //         move(Direction::Left);
    //     } else {
    //         move(Direction::Right);
    //     }
    // }
    // // std::cout << "x: " << m_pos.x << " y: " << m_pos.y << " dir: " << (int)m_dir << std::endl;
    // // end test
}