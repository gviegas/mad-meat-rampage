/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef GAME_OBJECT_HXX
#define GAME_OBJECT_HXX

#include "drawable.hxx"
#include "collidable.hxx"

class GameObject: public Drawable, public Collidable {
public:
    GameObject(sf::Vector2f fixedPos): m_id("") { m_fixedPos = fixedPos; }
    virtual ~GameObject() {}

    const sf::Vector2f& getFixedPosition() const { return m_fixedPos; }
    void setFixedPosition(sf::Vector2f fixedPos) { m_fixedPos = fixedPos; }

    virtual void update(double updateInterval) = 0;

    void setId(std::string id) { m_id = id; }
    const std::string& getId() const { return m_id; }
protected:
    sf::Vector2f m_fixedPos;
    std::string m_id;
};

#endif