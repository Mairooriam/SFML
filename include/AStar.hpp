#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "Node.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <unordered_set>
#include <cmath>

class Node;
class AStar {
public:
    static std::vector<Node*> findPath(Node* startNode, Node* goalNode, const std::vector<std::vector<Node>>& map);
    void printOpenNodes() const {
        // Create a copy of the priority queue
        PriorityQueue<Node*> copy = openNodes;

        // Print each node
        while (!copy.empty()) {
            Node *node = copy.top();
            //node->printNodeInfo();
            copy.pop();
        }
    }

    
private:
    PriorityQueue<Node*> openNodes;
    static float heuristic(const Node* a, const Node* b);
    static std::vector<Node*> getNeighbours(Node* node, const std::vector<std::vector<Node>>& grid);
};
#endif // ASTAR_HPP