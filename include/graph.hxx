/*
* Created by Gustavo Viegas (2016/10)
*/

#ifndef GRAPH_HXX
#define GRAPH_HXX

#include "definitions.hxx"
#include <vector>
#include <unordered_map>
#include <iostream>

struct Node {
    Node(int x, int y): m_x(x), m_y(y) {}
    int m_x, m_y;
};

struct Edge {
    Edge(Node* node, int cost, Movement move):
      m_node(node), m_cost(cost), m_move(move) {}
    Node* m_node;
    int m_cost;
    Movement m_move;
};

using Nodes = std::vector<Node>;
using Edges = std::vector<Edge>;
using Neighbors = std::unordered_map<Node*, Edges>;

class Graph {
public:
    Graph() {}
    ~Graph() {}

    void insert(Node node) {
        m_nodes.emplace_back(node);
    }

    void addEdges(Node* node, Edges edges) {
        m_neighbors[node] = edges;
    }

    Node* getNode(int x, int y) {
        for(auto& iter : m_nodes) {
            if(iter.m_x == x && iter.m_y == y) {
                return &iter;
            }
        }
        return nullptr;
    }

    Nodes* getNodes() {
        return &m_nodes;
    }

    Edges* getEdges(Node* node) {
        auto iter = m_neighbors.find(node);
        if(iter == m_neighbors.end()) { return nullptr; }
        return &iter->second;
    }

    // note: for debug...
    void print() {
        for(auto& node : m_nodes) {
            std::cout << "node: " << node.m_x << " " << node.m_y << std::endl;
            auto iter = m_neighbors.find(&node);
            if(iter == m_neighbors.end() || iter->second.empty()) {
                std::cout << "no neighbors..." << std::endl;
            } else {
                std::string str = "edges: ";
                for(auto& edge : iter->second) {
                    str += std::to_string(edge.m_node->m_x) + " ";
                    str += std::to_string(edge.m_node->m_y) + ", ";
                }
                std::cout << str << std::endl;
            }
            std::cout << std::endl;
        }
    }
private:
    Nodes m_nodes;
    Neighbors m_neighbors;
};

#endif