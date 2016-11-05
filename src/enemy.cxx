/*
* Created by Gustavo Viegas (2016/10)
*/

#include "enemy.hxx"
#include <ctime>

Enemy::Enemy(sf::Vector2f startPos): Character(startPos) {
    m_type = ObjectType::Enemy;
    m_dir = Direction::Left;
}
Enemy::~Enemy() {}

void Enemy::onCollision(Collidable* collidable, Axis axis) {
    if(collidable->getType() == ObjectType::Trap) {
        m_action = Action::Die;
    }
}

void Enemy::update(double updateInterval) {
    Character::update(updateInterval);
}