/*
* Created by Gustavo Viegas (2016/11)
*/

#include "key.hxx"

Key::Key(sf::Vector2f startPos): Usable(startPos) {
    m_type = ObjectType::Key;
    m_speed = {0.0, 0.0};
    m_impulse = 0.0;
    m_dir = Direction::Right;
}
Key::~Key() {}

void Key::animate(double updateInterval) {
    switch(m_dir) {
        case Direction::Left:
            m_animation.animate("Left", updateInterval);
            break;
        case Direction::Right:
            m_animation.animate("Right", updateInterval);
            break;
    }
}

void Key::onCollision(Collidable* collidable, Axis axis) {}