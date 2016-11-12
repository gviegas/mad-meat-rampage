/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef CHARACTER_HXX
#define CHARACTER_HXX

#include "game_being.hxx"
#include "animation.hxx"

class Character: public GameBeing {
public:
    Character(sf::Vector2f startPos);
    virtual ~Character();
    
    void loadConf(const std::string& fileName);

    void onTileCollision(sf::FloatRect tileRect, Axis axis);
    virtual void onCollision(Collidable* collidable, Axis axis) = 0;

    bool toRemove();
    Animation& getAnimation();
    
    void animate(double updateInterval);

    void update(double updateInterval);
    void draw(sf::RenderWindow* screen);
protected:
    Animation m_animation;
    bool m_removal;
    std::string m_id;
};

#endif