/*
* Created by Gustavo Viegas (2016/09)
*/

#include "st_menu.hxx"
#include "st_game.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

STMenu STMenu::m_this;

void STMenu::init() {
    loadConf("data/confs/menu.conf");
    for(auto& iter : m_buttons) {
        iter.second.setTexture(m_texture);
    }

    m_inputs = cgf::InputManager::instance();
    m_inputs->addMouseInput("Left-Click", sf::Mouse::Button::Left);
}

void STMenu::cleanup() {}

void STMenu::pause() {}
void STMenu::resume() {}

void STMenu::handleEvents(cgf::Game* game) {
    sf::RenderWindow* screen = game->getScreen();
    sf::Event event;
    while(screen->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            game->quit();
        }
    }

    if(m_inputs->testEvent("Left-Click")) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*screen);
        for(auto& iter : m_buttons) {
            sf::Vector2f buttonPos = iter.second.getPosition();
            sf::FloatRect buttonRect = iter.second.getLocalBounds();
            if(mousePos.x >= buttonPos.x && 
              mousePos.x <= buttonPos.x + buttonRect.width &&
              mousePos.y >= buttonPos.y &&
              mousePos.y <= buttonPos.y + buttonRect.height)
            {
                if(iter.first == ButtonType::Play) { 
                    game->changeState(STGame::instance());
                } else if(iter.first == ButtonType::Options) {
                    // todo: options state
                } else if(iter.first == ButtonType::Credits) {
                    // todo: credits state
                } else if(iter.first == ButtonType::Exit) {
                    game->quit();
                }
            }
        }
    }
}

void STMenu::update(cgf::Game* game) {
    sf::Vector2u screenSize = game->getScreen()->getSize();
    int offset = screenSize.y * 0.1;
    for(auto& iter : m_buttons) {
        sf::IntRect rect = iter.second.getTextureRect();
        iter.second.setPosition(screenSize.x / 2 - rect.width / 2,
          rect.top + offset);
    }
}

void STMenu::draw(cgf::Game* game) {
    sf::RenderWindow* screen = game->getScreen();
    for(auto& iter : m_buttons) {
        screen->draw(iter.second);
    }
}

void STMenu::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: STMenu::loadConf - " << fileName << std::endl; 
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "TEXTURE") {
                std::string texFile;
                sstream >> texFile;
                m_texture.loadFromFile(aux::getBasePath() + texFile);
            } else if(attr == "PLAY" || attr == "OPTIONS"
              || attr == "CREDITS" || attr == "EXIT") 
            {
                unsigned int width, height, row, column;
                sstream >> width >> height >> row >> column;
                sf::Sprite sprite;
                sprite.setTextureRect({column * width, row * height,
                  width, height});
                if(attr == "PLAY") {
                    m_buttons.emplace(ButtonType::Play, sprite);
                } else if(attr == "OPTIONS") {
                    m_buttons.emplace(ButtonType::Options, sprite);
                } else if(attr == "CREDITS") {
                    m_buttons.emplace(ButtonType::Credits, sprite);
                } else if(attr == "EXIT") {
                    m_buttons.emplace(ButtonType::Exit, sprite);
                }
            } 
        }
        file.close();
    }
}