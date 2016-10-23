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
    void search(const sf::Vector2u& from, const sf::Vector2u& to);

    void update(double updateInterval, Enemy* enemy, Player* player); // enemy and player params are for tests only
private:
    std::unordered_map<Node*, std::pair<Node*, Edge*>> m_path;
    //std::vector<Edge*> m_path;
    //TileMap* m_map;
    Graph m_graph;
};

#endif