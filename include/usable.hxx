/*
* Created by Gustavo Viegas (2016/11)
*/

#ifndef USABLE_HXX
#define USABLE_HXX

#include "game_being.hxx"
#include "animation.hxx"

class Usable: public GameBeing {
public:
    Usable(sf::Vector2f startPos);
    ~Usable();

    void loadConf(const std::string& fileName);

    bool isInUse();
    void setInUse(bool inUse);
    void setUser(GameBeing* user);
    GameBeing* getUser();

    void onTileCollision(sf::FloatRect tileRect, Axis axis);
    virtual void onCollision(Collidable* collidable, Axis axis) = 0;

    Animation& getAnimation();
    virtual void animate() = 0;

    void update(double updateInterval);
    void draw(sf::RenderWindow* screen);
protected:
    GameBeing* m_user;
    bool m_inUse;
    Animation m_animation;
};

#endif