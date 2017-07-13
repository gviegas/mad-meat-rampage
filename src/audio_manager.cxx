/*
* Created by Gustavo Viegas (2016/11)
*/

#include "audio_manager.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

AudioManager AudioManager::m_this;

void AudioManager::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: AudioManager::loadConf - "
          << fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "SOUND") {
                std::string name, soundFile;
                sstream >> name >> soundFile;
                m_buffers.emplace(name, sf::SoundBuffer());
                m_buffers.find(name)->second.loadFromFile(
                  aux::getBasePath() + soundFile);
                m_sounds.emplace(name, sf::Sound());
                m_sounds.find(name)->second.setBuffer(
                  m_buffers.find(name)->second);
            } else if(attr == "MUSIC") {
                // TODO
            }
        }
        file.close();
    }
}

void AudioManager::cleanup() {
    m_sounds.clear();
    m_buffers.clear();
}

void AudioManager::playSound(const std::string& name, bool loop) {
    auto iter = m_sounds.find(name);
    if(iter == m_sounds.end()) {
        std::cerr << "ERROR: AudioManager::playSound - " << name
          << " sound does not exist" << std::endl;
    } else {
        iter->second.setLoop(loop);
        iter->second.play();
    }
}

void AudioManager::stopSound(const std::string& name) {
    auto iter = m_sounds.find(name);
    if(iter == m_sounds.end()) {
        std::cerr << "ERROR: AudioManager::stopSound - " << name
          << " sound does not exist" << std::endl;
    } else {
        iter->second.stop();
    }
}

void AudioManager::playMusic(const std::string& name, bool loop) {} // TODO
void AudioManager::stopMusic(const std::string& name) {} // TODO
