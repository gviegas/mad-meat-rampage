/*
* Created by Gustavo Viegas (2016/11)
*/

#include "usable.hxx"
#include "aux.hxx"
#include "definitions.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

Usable::Usable(sf::Vector2f startPos):
  GameBeing(startPos), m_user(nullptr), m_animation(&m_sprite)
{
    m_inUse = false;
}
Usable::~Usable() {}

void Usable::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: Usable::loadConf - " << 
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
            } else if(attr == "ANIMATION") {
                std::string animFile;
                sstream >> animFile;
                m_animation.loadAnimation(animFile);
            }
        }
        file.close();
    }
}

bool Usable::isInUse() { return m_inUse; }
void Usable::setInUse(bool inUse) { m_inUse = inUse; }
void Usable::setUser(GameBeing* user) { m_user = user; }
GameBeing* Usable::getUser() {return m_user; }
Animation& Usable::getAnimation() { return m_animation; }

void Usable::onTileCollision(sf::FloatRect tileRect, Axis axis) {
    if(m_inUse) { return; } // no need to check tile collision if in use

    if(axis == Axis::Y) {
        setVelocity({m_velocity.x, 0.0});
        if(m_pos.y < tileRect.top) {
            setPosition({m_pos.x, tileRect.top - m_bBox.height});
            if(m_action != Action::Die) {
                m_action = m_velocity.x ? Action::Walk : Action::None;
            }
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
        m_action = m_velocity.y ? Action::Jump : Action::None;
    }
}

void Usable::update(double updateInterval) {
    if(m_inUse && m_user) {
        setPosition(m_user->getPosition());
        setDirection(m_user->getDirection());
    } else {
        float delta = (float)(updateInterval / 1000); 
        move(m_velocity * delta);
        accelerate({0.0, 300.0 * delta});
        addVelocity(m_acceleration);
        setAcceleration({0.0, 0.0});
    }
    m_sprite.setPosition(m_pos);
    m_bBox.left = m_pos.x;
    m_bBox.top = m_pos.y;
    animate();
}

void Usable::draw(sf::RenderWindow* screen) {
    screen->draw(m_sprite);
}