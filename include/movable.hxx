/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef MOVABLE_HXX
#define MOVABLE_HXX

enum class Direction { Left = 0, Right };

class Movable {
public:
    Movable() {}
    ~Movable() {}

    void move(sf::Vector2f vec) {
        m_oldPos = m_pos;
        m_pos += vec;
    }

    // void move(Direction dir) {
    //     m_oldPos = m_pos;
    //     if(dir == Direction::Left) { m_pos -= m_speed; }
    //     else { m_pos += m_speed; }
    // }

    void move(Direction dir) {
        if(dir == Direction::Left) { accelerate({-m_speed.x, 0.0}); }
        else { accelerate({m_speed.x, 0.0}); }
    }

    void jump(float impulse) {
       if(impulse > 0) { addVelocity({0.0, -impulse}); }
       else { addVelocity({0.0, impulse}); }
    }

    void changeDirection() {
        m_dir = m_dir == Direction::Left ?
          Direction::Right : Direction::Left;
        m_dirChanged = true; 
    }
    void setPosition(sf::Vector2f vec) {  m_oldPos = m_pos; m_pos = vec; }
    void setSpeed(sf::Vector2f vec) { m_speed = vec; }
    void setAcceleration(sf::Vector2f vec) { m_acceleration = vec; }
    void accelerate(const sf::Vector2f& vec) { m_acceleration += vec; }
    void setVelocity(sf::Vector2f vec) { m_velocity = vec; }
    void addVelocity(const sf::Vector2f& vec) { m_velocity += vec; }

    const sf::Vector2f& getPosition() { return m_pos; }
    Direction getDirection() { return m_dir; }
protected:
    Direction m_dir;
    bool m_dirChanged;
    sf::Vector2f m_pos;
    sf::Vector2f m_oldPos;
    sf::Vector2f m_speed;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_velocity;
    float m_impulse;
};

#endif