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
    Drawable(): m_texture(nullptr) {}
    virtual ~Drawable() {} //{ delete m_texture; } // call me child // (11/5) satan? is that  you?

    void create(const std::string& texFile) {
        m_texture = new sf::Texture();
        m_texture->loadFromFile(aux::getBasePath() + texFile);
        m_sprite.setTexture(*m_texture);
    }

    void destroy() { delete m_texture; } // only the last instance of this Drawable should call destroy() - beware with any copies still alive

    // void create(const sf::Texture& texture) {
    //     m_sprite.setTexture(texture);
    // }

    sf::Texture* getTexture() { return m_texture; } // testing 
    sf::Sprite* getSprite() { return &m_sprite; } // testing

    virtual void draw(sf::RenderWindow* screen) = 0;
protected:
    sf::Sprite m_sprite;
private:
    sf::Texture* m_texture; // clones will share this
};

#endif