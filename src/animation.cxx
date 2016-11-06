/*
* Created by Gustavo Viegas (2016/10)
*/

#include "animation.hxx"
#include "aux.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

Animation::Animation(sf::Sprite* sprite): m_sprite(sprite), m_currentAnim("") {
    m_isPlaying = false;
    m_isStopped = false;
    m_isLooping = false;
}
Animation::~Animation() {}

void Animation::loadAnimation(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: Animation::loadAnimation - " <<
          fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "ANIMATION") {
                std::string animation;
                sf::IntRect rect;
                unsigned int totalFrames;
                sstream >> animation;
                sstream >> rect.left >> rect.top >> rect.width >> rect.height;
                sstream >> totalFrames;
                m_animations.emplace(animation, AnimInfo(rect, totalFrames));
            }
        }
        file.close();
    }
}

void Animation::setSprite(sf::Sprite* sprite) {
    m_sprite = sprite;
}

void Animation::animate(std::string animation) {
    if(m_isPlaying && animation == m_currentAnim) { play(); }
    else {
        auto iter = m_animations.find(animation);
        if(iter == m_animations.end()) {
            std::cerr << "ERROR: Animation::animate - " <<
              animation << std::endl;
        } else {
            m_currentRect = iter->second.m_rect;
            m_currentAnim = animation;
            m_frameRange = {0, iter->second.m_totalFrames};
            m_isPlaying = true;
            play();
        }
    }
}

void Animation::play() {
    if(m_frameRange.x == m_frameRange.y) {
        if(m_isLooping) { m_frameRange.x = 0; }
        else { m_isPlaying = false; return; }
    }
    m_currentRect.left = m_frameRange.x++ * m_currentRect.width;
    m_sprite->setTextureRect(m_currentRect);

}

void Animation::stop() {}
void Animation::restart() {}

void Animation::setLoop(bool loop) { m_isLooping = loop; }

const sf::IntRect& Animation::getCurrentRect() const { return m_currentRect; }
const std::string& Animation::getCurrentAnim() const { return m_currentAnim; }
const sf::Vector2i& Animation::getFrameRange() const { return m_frameRange; }