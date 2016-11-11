/*
* Created by Gustavo Viegas (2016/09)
*/

#include "definitions.hxx"
#include "st_begin.hxx"

int main(int argc, char** argv) {
    cgf::Game game(10, 30);
    game.init("mmr-sfml-ed2016/2", SCREEN_WIDTH, SCREEN_HEIGHT, true);
    game.changeState(STBegin::instance());
    while(game.isRunning()) {
        game.handleEvents();
        game.update();
        game.draw();
    }
    game.clean();
    return 0;
}