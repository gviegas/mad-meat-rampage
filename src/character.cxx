/*
* Created by Gustavo Viegas (2016/09)
*/

#include "character.hxx"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

Character::Character(sf::Vector2f startPos): GameBeing(startPos) {}
Character::~Character() {}

void Character::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: Character::loadConf - " << 
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
            } else if(attr == "SPEED") {
                float x, y;
                sstream >> x >> y;
                m_speed = {x, y};
            } else if(attr == "IMPULSE") {
                sstream >> m_impulse;
            }
        }
        file.close();
    }
}

void Character::onTileCollision(sf::FloatRect tileRect, Axis axis) {
    if(axis == Axis::Y) {
        setVelocity({m_velocity.x, 0.0});
        if(m_pos.y < tileRect.top) {
            setPosition({m_pos.x, tileRect.top - m_bBox.height});
            m_action = Action::None;
        } else if(m_pos.y > tileRect.top) {
            setPosition({m_pos.x, tileRect.top + tileRect.height});
            m_action = Action::Jump;
        }
    } else if(axis == Axis::X) {
        setVelocity({0.0, m_velocity.y});
        if(m_pos.x < tileRect.left) {
            setPosition({tileRect.left - m_bBox.width, m_pos.y}); 
        } else if(m_pos.x > tileRect.left) {
            setPosition({tileRect.left + tileRect.width, m_pos.y});
        }
    }
}

void Character::update(sf::RenderWindow* screen) {
    // testing block
    //if(m_dirChanged) { 
    //    m_dirChanged = false;
    //    m_sprite.scale({-1.0, 1.0});
    //} else { 
    //}
    // end testing
    
    if(m_velocity.y) { m_action = Action::Jump; } // note: it's a float...

    move(m_velocity);
    accelerate({0.0, 0.5});
    addVelocity(m_acceleration);
    setAcceleration({0.0, 0.0});
    m_sprite.setPosition(m_pos);
    m_bBox.left = m_pos.x;
    m_bBox.top = m_pos.y;
}

void Character::draw(sf::RenderWindow* screen) {
    screen->draw(m_sprite);
}