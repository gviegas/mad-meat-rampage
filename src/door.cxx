/*
* Created by Gustavo Viegas (2016/11)
*/

#include "door.hxx"
#include "aux.hxx"
#include "definitions.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

Door::Door(sf::Vector2f fixedPos): GameObject(fixedPos), m_warp(true) {
    m_type = ObjectType::Door;
}
Door::~Door() {}

void Door::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: Door::loadConf - " << fileName << std::endl;
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
                int left, top, width, height;
                sstream >> left >> top >> width >> height;
                m_bBox = {left, top, width, height};
            }
        }
        file.close();
    }
}

void Door::onTileCollision(sf::FloatRect tileRect, Axis axis) {}
void Door::onCollision(Collidable* collidable, Axis axis) {}

void Door::setWarp(bool warp) { m_warp = warp; }
bool Door::isWarp() { return m_warp; }

// TODO: only works if bbox == dimension
void Door::update(double updateInterval) {
    m_sprite.setPosition(m_fixedPos);
    m_bBox.left = m_fixedPos.x;
    m_bBox.top = m_fixedPos.y;
}

void Door::draw(sf::RenderWindow* screen) {
    screen->draw(m_sprite);
}
