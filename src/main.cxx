/*
* Created by Gustavo Viegas (2016/09)
*/

#include "st_begin.hxx"

int main(int argc, char** argv) {
    cgf::Game game(10, 30);
    game.init("mmr-sfml-ed2016/2", 1280, 960, false);
    game.changeState(STBegin::instance());
    while(game.isRunning()) {
        game.handleEvents();
        game.update();
        game.draw();
    }
    game.clean();
    return 0;
}