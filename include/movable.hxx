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

    void move(Direction dir) {
        m_oldPos = m_pos;
        if(dir == Direction::Left) { m_pos -= m_speed; }
        else { m_pos += m_speed; }
    }

    void changeDirection(Direction dir) { m_dir = dir; m_dirChanged = true; }
    void setPosition(sf::Vector2f vec) {  m_oldPos = m_pos; m_pos = vec; }
    void setSpeed(sf::Vector2f vec) { m_speed = vec; }
    void accelerate(const sf::Vector2f& vec) { m_speed += vec; }
protected:
    Direction m_dir;
    bool m_dirChanged;
    sf::Vector2f m_pos;
    sf::Vector2f m_oldPos;
    sf::Vector2f m_speed;
    //sf::Vector2f m_acceleration;
};

#endif