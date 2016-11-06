/*
* Created by Gustavo Viegas (2016/11)
*/

#include "ui.hxx"
#include "aux.hxx"
#include "definitions.hxx"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

UI::UI(int digits) {
    m_digits = digits < 1 ? 1 : digits;
    for(int i = 0; i < digits; ++i) { m_numbers.emplace_back(sf::Sprite()); }
    loadConf("data/confs/ui.conf");
}
UI::~UI() { m_numbers.clear(); }

void UI::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: UI::loadConf - " << fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "LABEL") {
                std::string texFile;
                sstream >> texFile;
                m_labelTex.loadFromFile(aux::getBasePath() + texFile);
                m_label.setTexture(m_labelTex);
            } else if(attr == "NUMBERS") {
                std::string texFile;
                int numberWidth, numberHeight;
                sstream >> texFile >> numberWidth >> numberHeight;
                m_numbersTex.loadFromFile(aux::getBasePath() + texFile);
                for(auto& iter: m_numbers) {
                    iter.setTexture(m_numbersTex);
                    iter.setTextureRect({0, 0, numberWidth, numberHeight});
                }
            }
        }
        file.close();
    }
}

void UI::update(int score, double updateInterval) {
    m_score = score;
    sf::IntRect rect;

    for(int i = 0, m = pow(10, m_digits - 1);
      i < m_digits; ++i, m = pow(10, m_digits - 1 - i))
    {
        rect = m_numbers[i].getTextureRect();
        m_numbers[i].setTextureRect(
          {score / m * rect.width, rect.top, rect.width, rect.height});
        m_numbers[i].setPosition(sf::Vector2f(
          SCREEN_WIDTH - rect.width * (m_digits - i), 0));
        score %= m;
    }

    m_label.setPosition(sf::Vector2f(
        SCREEN_WIDTH - m_labelTex.getSize().x - rect.width * m_digits, 0));
}

void UI::draw(sf::RenderWindow* screen) {
    screen->draw(m_label);
    for(auto& iter : m_numbers) { screen->draw(iter); }
}