/*
* Created by Gustavo Viegas (2016/09)
*/

#include "character.hxx"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

Character::Character(sf::Vector2f startPos): GameBeing(startPos),
  m_animation(&m_sprite)
{
    m_removal = false;
    m_animation.setLoop(true);
}
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
            } else if(attr == "ANIMATION") {
                std::string animFile;
                sstream >> animFile;
                m_animation.loadAnimation(animFile);
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
            m_action = m_velocity.x ? Action::Walk : Action::None;
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
       //std::cout << "collided on x!: " << (int)m_type << std::endl; // testing
    }
}

bool Character::toRemove() { return m_removal; }

void Character::animate() {
    // test block
    // just testing die animation/state - have to finish animation class...
    if(m_animation.getCurrentAnim() == "Die" && 
      m_animation.getFrameRange().x == m_animation.getFrameRange().y) 
    { 
        m_removal = true;
        return; 
    }
    //m_animation.setLoop(true);
    // end test
    switch(m_action) {
        case Action::None:
            m_dir == Direction::Left ? m_animation.animate("Idle-Left")
              : m_animation.animate("Idle-Right");
            break;
        case Action::Walk:
            m_dir == Direction::Left ? m_animation.animate("Walk-Left")
              : m_animation.animate("Walk-Right");
            break;
        case Action::Jump:
            m_dir == Direction::Left ? m_animation.animate("Jump-Left")
              : m_animation.animate("Jump-Right");
            break;
        case Action::Die:
            m_animation.setLoop(false); // testing
            m_animation.animate("Die");
            break;
    }
}

// todo: there's some inconsistency with the character actions...
// it should not be set only by the collision method... check the velocity here perhaps?
void Character::update(double updateInterval) {
    //if(m_velocity.y) { m_action = Action::Jump; } // note: it's a float...
    //else if(m_velocity.x) { m_action = Action::Walk; } // same as above...
    //else { m_action = Action::None; }

    // move(m_velocity);
    // accelerate({0.0, 0.5});
    // addVelocity(m_acceleration);
    // setAcceleration({0.0, 0.0});
    // m_sprite.setPosition(m_pos);
    // m_bBox.left = m_pos.x;
    // m_bBox.top = m_pos.y;

    if(m_action != Action::Die) {
        float delta = (float)(updateInterval / 1000);

        move(m_velocity * delta);
        accelerate({0.0, 300.0 * delta});
        addVelocity(m_acceleration);
        setAcceleration({0.0, 0.0});
        m_sprite.setPosition(m_pos);
        // todo: only works if bbox == dimension - correct this
        m_bBox.left = m_pos.x;
        m_bBox.top = m_pos.y;
    }
    
    animate();
}

void Character::draw(sf::RenderWindow* screen) {
    screen->draw(m_sprite);
}