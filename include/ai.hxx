/*
* Created by Gustavo Viegas (2016/10)
*/

#ifndef AI_HXX
#define AI_HXX

#include "graph.hxx"
#include "tile_map.hxx"
#include <queue>

#include "enemy.hxx"
#include "player.hxx"

class AI {
public:
    AI();
    ~AI();

    void createGraph(TileMap* map);
    void act(Character* actor, Character* target);
private:
    std::vector<Edge*> search(const sf::Vector2u& from, const sf::Vector2u& to);
    std::unordered_map<Node*, std::pair<Node*, Edge*>> m_path;
    Graph m_graph;
    Movement m_lastMove;
};

#endif