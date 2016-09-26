/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef DRAWABLE_HXX
#define DRAWABLE_HXX

#include "aux.hxx"
#include <string>
#include <SFML/Graphics.hpp>

class Drawable {
public:
    Drawable() {}
    virtual ~Drawable() {}

    void create(const std::string& texFile) {
        m_texture.loadFromFile(aux::getBasePath() + texFile);
        m_sprite.setTexture(m_texture);
    }

    virtual void draw(sf::RenderWindow* screen) = 0;
protected:
    sf::Sprite m_sprite;
private:
    sf::Texture m_texture;
};

#endif