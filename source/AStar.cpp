#include "AStar.hpp"
#include "priorityQueue.hpp"



std::vector<Node *> AStar::findPath(Node *startNode, Node *goalNode, const std::vector<std::vector<Node>> &map)
{
    startNode->gCost = 0;

    
    return std::vector<Node *>();
}

float AStar::heuristic(const Node *a, const Node *b)
{
    return std::abs(a->getPosition().x - b->getPosition().x) + std::abs(a->getPosition().y - b->getPosition().y);
}
