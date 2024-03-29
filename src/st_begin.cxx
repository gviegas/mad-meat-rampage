/*
* Created by Gustavo Viegas (2016/09)
*/

#include "st_begin.hxx"
#include "st_menu.hxx"
#include "audio_manager.hxx"
#include <iostream>

STBegin STBegin::m_this;

void STBegin::init() {
    AudioManager::instance()->loadConf("data/confs/audio.conf");
    AudioManager::instance()->playSound("Intro");

    if(m_initiated) { return; }

    m_texture.loadFromFile("data/textures/title-begin.png");
    m_bg.setTexture(m_texture);
    m_font.loadFromFile("data/fonts/LiberationSans-Regular.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(26);
    m_text.setString("Press ENTER to play");

    m_inputs = cgf::InputManager::instance();
    m_inputs->addKeyInput("Quit", sf::Keyboard::Escape);
    m_inputs->addKeyInput("Enter", sf::Keyboard::Return);
}
void STBegin::cleanup() { m_initiated = true; }

void STBegin::pause() {}
void STBegin::resume() {}

void STBegin::handleEvents(cgf::Game* game) {
    sf::RenderWindow* screen = game->getScreen();
    sf::Event event;
    while(screen->pollEvent(event)) {
        if(event.type == sf::Event::Closed ||
          m_inputs->testEvent("Quit"))
        {
            game->quit();
        }
    }

    if(m_inputs->testEvent("Enter")) {
        AudioManager::instance()->stopSound("Intro");
        game->changeState(STMenu::instance());
    }
}

void STBegin::update(cgf::Game* game) {
    sf::Vector2f viewSize = game->getScreen()->getView().getSize();
    m_bg.setPosition(viewSize.x / 2 - m_texture.getSize().x / 2, 0.0);
    sf::FloatRect rect = m_text.getLocalBounds();
    m_text.setPosition(viewSize.x / 2 - rect.width / 2,
      (viewSize.y / 2 - rect.height / 2) * 1.7);
}

void STBegin::draw(cgf::Game* game) {
    sf::RenderWindow* screen = game->getScreen();
    screen->draw(m_bg);
    screen->draw(m_text);
}
