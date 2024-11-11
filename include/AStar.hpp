#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "Node.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <unordered_set>
#include <cmath>
// Define the CompareNode struct

class Node;
class AStar {
public:
    void initAStar(Node* startNode, Node* goalNode);
    std::vector<Node*> findPathOneStep();
    
    void printOpenNodes() const {
        // Create a copy of the priority queue
        PriorityQueue<Node*> copy = openNodes;
        
        //std::cout << "STARTING PRINTING" << "\n";
        while (!copy.empty()) {
            Node* node = copy.top();
            std::cout << *node << std::endl; // Use the << operator
            copy.pop();
        }
    }
    void resetPathFinder();
    
private:
    Node* goalNode;
    Node* currentNode = nullptr;
    std::vector<Node*> path;
    PriorityQueue<Node*> openNodes;
    std::unordered_set<Node*> openNodesSet;
    std::unordered_set<Node*> closedNodes;
    static float heuristic(const Node* a, const Node* b);
    static std::vector<Node*> getNeighbours(Node* node, const std::vector<std::vector<Node>>& grid);


        // Debug print method
    static void debugPrint(const std::string& message) {
        if (debugEnabled) {
            std::cout << message << std::endl;
        }
    }
    static void enableDebug() { debugEnabled = true; }
    static void disableDebug() { debugEnabled = false; }
    static bool debugEnabled;
};
#endif // ASTAR_HPP