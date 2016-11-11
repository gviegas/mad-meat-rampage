/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef GAME_BEING_HXX
#define GAME_BEING_HXX

#include "drawable.hxx"
#include "collidable.hxx"
#include "movable.hxx" 

enum class Action { None = 0, Walk, Jump, Die };

class GameBeing: public Drawable, public Collidable, public Movable {
public:
    GameBeing(sf::Vector2f startPos): m_id("") { 
        m_pos = m_oldPos = startPos;
        m_action = Action::None; 
    }
    virtual ~GameBeing() {}

    Action getAction() { return m_action; }
    void setAction(Action action) {  m_action = action; }

    virtual void update(double updateInterval) = 0;

    void setId(std::string id) { m_id = id; }
    const std::string& getId() const { return m_id; }
protected:
    Action m_action;
    std::string m_id;
};

#endif