/*
* Created by Gustavo Viegas (2016/10)
*/

#include "ai.hxx"

AI::AI() { m_lastMove = Movement::Idle; }
AI::~AI() {}

void AI::createGraph(TileMap* map) {
    for(unsigned int i = 0; i < map->getGridSize().x; ++i) {
        for(unsigned int j = 1; j < map->getGridSize().y; ++j) {
            if(map->checkTile({i, j})) {
                m_graph.insert({static_cast<int>(i), static_cast<int>(j)});
            }
        }
    }
    // create edges to adjacent tiles
    int x, y, range = 3;
    for(auto& iter : *m_graph.getNodes()) {
        x = iter.m_x;
        y = iter.m_y;
        Edges edges;
        Node* node = nullptr;
        for(int i = 1; i <= range; ++i) {
            for(int j = 1; j <= range; ++j) {
                if((node = m_graph.getNode(x - i, y)) != nullptr) {
                    edges.emplace_back(Edge(node, 1, Movement::Left));
                }
                if((node = m_graph.getNode(x + i, y)) != nullptr) {
                    edges.emplace_back(Edge(node, 1, Movement::Right));
                }
                if((node = m_graph.getNode(x - i, y - j)) != nullptr) {
                    edges.emplace_back(Edge(node, 1, Movement::JumpLeft));
                }
                if((node = m_graph.getNode(x - i, y + j)) != nullptr) {
                    edges.emplace_back(Edge(node, 1, Movement::Left));
                }
                if((node = m_graph.getNode(x + i, y - j)) != nullptr) {
                    edges.emplace_back(Edge(node, 1, Movement::JumpRight));
                }
                if((node = m_graph.getNode(x + i, y + j)) != nullptr) {
                    edges.emplace_back(Edge(node, 1, Movement::Right));
                }
            }
        }
        m_graph.addEdges(&iter, edges);
    }
}

std::vector<Edge*> AI::search(const sf::Vector2u& from, const sf::Vector2u& to) {
    // Node* start = m_graph.getNode(from.x / TILE_WIDTH, from.y / TILE_HEIGHT + 1);
    // Node* goal = m_graph.getNode(to.x / TILE_WIDTH, to.y / TILE_HEIGHT + 1);
    Node* start = m_graph.getNode(from.x, from.y + 1);
    Node* goal = m_graph.getNode(to.x, to.y + 1);
    if(start == nullptr) {
        //std::cerr << "ERROR: no node at " << from.x / 64 <<
        //  " " << from.y / 64 + 1<< std::endl;
    } else if(goal == nullptr) {
        //std::cerr << "ERROR: no node at " << to.x / 64 <<
        //  " " << to.y / 64 + 1 << std::endl;
    } else {
        m_path.clear();
        std::queue<Node*> frontier;
        frontier.push(start);
        m_path.emplace(start, std::make_pair(nullptr, nullptr));
        while(!frontier.empty()) {
            Node* current = frontier.front();
            frontier.pop();
            for(auto& edge : *m_graph.getEdges(current)) {
                if(m_path.find(edge.m_node) == m_path.end()) {
                    frontier.push(edge.m_node);
                    m_path.emplace(edge.m_node,
                      std::make_pair(current, &edge));
                }
            }
        }
        std::vector<Edge*> steps;
        Edge* edge = nullptr;
        auto iter = m_path.find(goal);
        while(iter != m_path.end() && iter->second.first) {
            edge = iter->second.second;
            steps.push_back(edge);
            iter = m_path.find(iter->second.first);
        }
        return steps;
    }
    std::vector<Edge*> empty;
    return empty;
}

void AI::act(Character* actor, Character* target, double updateInterval) {
    float delta = (float)(updateInterval / 1000);

    std::vector<Edge*> steps = search(
      {static_cast<unsigned int>(actor->getPosition().x / actor->getBBox().width),
      static_cast<unsigned int>(actor->getPosition().y / actor->getBBox().height)},
      {static_cast<unsigned int>(target->getPosition().x / target->getBBox().width),
      static_cast<unsigned int>(target->getPosition().y / target->getBBox().height)});

    if(actor->getAction() == Action::Jump) {
        if(m_lastMove == Movement::JumpLeft) {
            //actor->move(Direction::Left);
            actor->accelerate({-30 * delta, 0});
        } else if(m_lastMove == Movement::JumpRight) {
            //actor->move(Direction::Right);
            actor->accelerate({30 * delta, 0});
        }
    }

    if(steps.size()) {
        Edge* nextStep = steps.back();
        Movement nextMove = nextStep->m_move;
        switch(nextMove) {
            case Movement::Left:
                if(actor->getDirection() != Direction::Left) {
                    actor->changeDirection();
                }
                actor->move(Direction::Left);
                break;
            case Movement::Right:
                if(actor->getDirection() != Direction::Right) {
                    actor->changeDirection();
                }
                actor->move(Direction::Right);
                break;
            case Movement::JumpLeft:
                if(actor->getDirection() != Direction::Left) {
                    actor->changeDirection();
                }
                actor->setAction(Action::Jump);
                actor->jump();
                break;
            case Movement::JumpRight:
                if(actor->getDirection() != Direction::Right) {
                    actor->changeDirection();
                }
                actor->setAction(Action::Jump);
                actor->jump();
                break;
            case Movement::Jump:
                actor->setAction(Action::Jump);
                actor->jump();
                break;
        }
        m_lastMove = nextMove;
    }
}
