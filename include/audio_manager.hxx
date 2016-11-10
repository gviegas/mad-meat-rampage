/*
* Created by Gustavo Viegas (2016/11)
*/

#ifndef AUDIO_MANAGER_HXX
#define AUDIO_MANAGER_HXX

#include "aux.hxx"
#include <unordered_map>
#include <SFML/Audio.hpp>

using SoundBuffers = std::unordered_map<std::string, sf::SoundBuffer>;
using Sounds = std::unordered_map<std::string, sf::Sound>; 

class AudioManager {
public:
    void loadConf(const std::string& fileName);
    void cleanup();

    void playSound(const std::string& name, bool loop = false);
    void stopSound(const std::string& name);
    void playMusic(const std::string& name, bool loop = true);
    void stopMusic(const std::string& name);

    static AudioManager* instance() { return &m_this; }
protected:
    AudioManager() {}
private:
    static AudioManager m_this;
    SoundBuffers m_buffers;
    Sounds m_sounds;
};

#endif