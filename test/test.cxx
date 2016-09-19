/*
* Created by Gustavo Viegas (2016/09)
*/

#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    sf::RenderWindow wnd(sf::VideoMode(800, 600), "test");
    while(wnd.isOpen()) {
        sf::Event event;
        while(wnd.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                wnd.close();
            }
        }
        wnd.clear(sf::Color::White);
        wnd.display();
    }
    return -1;
}