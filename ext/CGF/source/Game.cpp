/*
 *  Game.cpp
 *  Main game class
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 *
 * NOTICE: Changed by Gustavo Viegas on 2017/07
 *
 */

#include "Game.h"
#include "GameState.h"

#include <iostream>
#include <assert.h>
#include <cmath>

namespace cgf
{

using namespace std;

// Construtor
Game::Game(int minFrameRate, int maxFrameRate)
{
    this->minFrameRate = minFrameRate;
    this->maxFrameRate = maxFrameRate;
    updateInterval = 1.0 / maxFrameRate*1000;
    cout << "Update interval: " << updateInterval << endl;
    maxCyclesPerFrame = (double) maxFrameRate / minFrameRate;
    lastFrameTime = 0;
    cyclesLeftOver = 0;

    // Load the font; exit on error.
    if (!font.loadFromFile("data/fonts/arial.ttf"))
    {
        sf::err() << "Failed to load arial.ttf";
        exit(EXIT_FAILURE);
    }

    showStats = false;
    hud = new ClockHUD(clock, font);
    clock.setSampleDepth(100); // Sample 100 frames for averaging.
}

/*
* init(): Last modified on 2017/07 by Gustavo Viegas
*/
void Game::init(const char* title, int width, int height, bool fullscreen)
{
    auto mode = sf::VideoMode(width, height);
    if(fullscreen) {
      if(mode.isValid())
        screen = new sf::RenderWindow(mode, title, sf::Style::Fullscreen);
      else
        screen = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), title,
          sf::Style::Fullscreen);
    } else
      screen = new sf::RenderWindow(mode, title);

    auto ws = screen->getDefaultView().getSize();
    float w = ws.y / 3 * 4;
    float off = (ws.x - w) / 2;

    sf::View view;
    view.reset(sf::FloatRect(0, 0, 1280.0, 960.0));
    view.setViewport(sf::FloatRect(off / ws.x, 0, w / ws.x, 1));
    screen->setView(view);

    originalView = screen->getView();
    this->fullscreen = fullscreen;
    running = true;
	  cout << "Game Initialised Succesfully" << endl;
}

void Game::handleEvents()
{
    states.top()->handleEvents(this);
}

void Game::changeState(GameState* state)
{
    // cleanup the current state
    if ( !states.empty() ) {
        states.top()->cleanup();
        states.pop();
    }

    // store and init the new state
    states.push(state);
    states.top()->init();
}

void Game::pushState(GameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.top()->pause();
	}

	// store and init the new state
	states.push(state);
	states.top()->init();
}

void Game::popState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.top()->cleanup();
		states.pop();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.top()->resume();
	}
}

void Game::update()
{
    double currentTime, updateIterations;

    currentTime = gameClock.getElapsedTime().asMilliseconds();
    updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);

    if (updateIterations > maxCyclesPerFrame * updateInterval) {
        updateIterations = maxCyclesPerFrame * updateInterval;
    }

    // int cont = 1;
    while(updateIterations > updateInterval) {
        updateIterations -= updateInterval;
        //cout << "updating " << cont++ << endl;
        if ( !states.empty() )
            states.top()->update(this);
    }
    cyclesLeftOver = updateIterations;
    lastFrameTime = currentTime;
}

void Game::draw()
{
    // let the state draw the screen
    screen->clear();
    clock.beginFrame();
    states.top()->draw(this);

    if(showStats)
    {
        // Draw the frame statistics.
        sf::View view = screen->getView();
        sf::Vector2f pos = originalView.getCenter() - originalView.getSize()/2.f;
        hud->setPosition(pos); //cout << "screen " << screen << endl;
        screen->setView(originalView);
        screen->draw(*hud);
        screen->setView(view);
    }
    screen->display();
    clock.endFrame();
}

void Game::clean()
{
    while ( !states.empty() ) {
		states.top()->cleanup();
		states.pop();
    }
    delete hud;
    delete screen;
}

} // namespace cgf
