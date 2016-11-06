/*
* Created by Gustavo Viegas (2016/10)
*/

#ifndef ANIMATION_HXX
#define ANIMATION_HXX

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

struct AnimInfo {
    AnimInfo(sf::IntRect rect, unsigned int totalFrames):
      m_rect(rect), m_totalFrames(totalFrames) {}
    sf::IntRect m_rect;
    unsigned int m_totalFrames;
};

using Animations = std::unordered_map<std::string, AnimInfo>;

class Animation {
public:
    Animation(sf::Sprite* sprite);
    ~Animation();

    void loadAnimation(const std::string& fileName);
    void setSprite(sf::Sprite* sprite);

    void animate(std::string animation);
    void play();
    void stop();
    void restart();
    void setLoop(bool loop);
    
    const sf::IntRect& getCurrentRect() const;
    const std::string& getCurrentAnim() const;
    const sf::Vector2i& getFrameRange() const;
private:
    Animations m_animations;
    sf::Sprite* m_sprite;
    sf::IntRect m_currentRect;
    std::string m_currentAnim;
    sf::Vector2i m_frameRange;
    bool m_isPlaying;
    bool m_isStopped;
    bool m_isLooping;
};

#endif