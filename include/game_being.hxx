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
    GameBeing(sf::Vector2f startPos) { 
        m_pos = m_oldPos = startPos;
        m_action = Action::None; 
    }
    virtual ~GameBeing() {}
    
    Action getAction() { return m_action; }
    void setAction(Action action) {  m_action = action; }

    virtual void update(double updateInterval) = 0;
protected:
    Action m_action;
};

#endif