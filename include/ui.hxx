/*
* Created by Gustavo Viegas (2016/11)
*/

#ifndef UI_HXX
#define UI_HXX

#include <SFML/Graphics.hpp>
#include <vector>

class UI {
public:
    UI(int digits = 3);
    ~UI();

    void loadConf(const std::string& fileName);

    void update(int score, double updateInterval);
    void draw(sf::RenderWindow* screen);
private:
    sf::Texture m_labelTex;
    sf::Texture m_numbersTex;
    sf::Sprite m_label;
    std::vector<sf::Sprite> m_numbers;
    int m_digits;
    int m_score;
};

#endif