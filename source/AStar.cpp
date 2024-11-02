#include "AStar.hpp"

float AStar::heuristic(const Node* a, const Node* b) {
    return std::abs(a->getPosition().x - b->getPosition().x) + std::abs(a->getPosition().y - b->getPosition().y);
}