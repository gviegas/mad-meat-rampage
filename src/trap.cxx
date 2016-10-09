/*
* Created by Gustavo Viegas (2016/10)
*/

#include "trap.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

Trap::Trap(sf::Vector2f fixedPos): GameObject(fixedPos), 
  m_animation(&m_sprite) 
{
    m_type = ObjectType::Trap;

    m_animation.loadAnimation("data/animations/trap1.anim");
    m_animation.setLoop(true);
}
Trap::~Trap() {}

void Trap::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: Trap::loadConf - " <<
          fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "TEXTURE") {
                std::string texFile;
                sstream >> texFile;
                create(texFile);
            } else if(attr == "BBOX") {
                float left, top, width, height;
                sstream >> left >> top >> width >> height;
                m_bBox = {left, top, width, height};
            }
        }
        file.close();
    }
}

void Trap::onTileCollision(sf::FloatRect tileRect, Axis axis) {}
void Trap::onCollision(Collidable* collidable, Axis axis) {}

// todo: only works if bbox == dimension - correct this
void Trap::update(double updateInterval) {
    m_sprite.setPosition(m_fixedPos);
    m_bBox.left = m_fixedPos.x;
    m_bBox.top = m_fixedPos.y;
    m_animation.animate("Rotate"); 
}
void Trap::draw(sf::RenderWindow* screen) {
    screen->draw(m_sprite);
}