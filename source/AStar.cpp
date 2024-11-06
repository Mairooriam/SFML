#include "AStar.hpp"
#include "priorityQueue.hpp"

bool AStar::debugEnabled = true; // Define the static member
void AStar::initAStar(Node *startNode, Node *goalNode)
{   
    this->goalNode = goalNode;
    startNode->updateAStarValues();
    openNodesSet.insert(startNode); // Add to set
    openNodes.push(startNode);
}

std::vector<Node *> AStar::findPathOneStep()
{

    while (!openNodes.empty()) {
        Node* currentNode = openNodes.top();
        openNodes.pop();
        openNodesSet.erase(currentNode); // Remove from set

        if (currentNode == goalNode) {
            std::vector<Node*> path;
            while (currentNode != nullptr) {
                path.push_back(currentNode);
                currentNode = currentNode->parent;
            }
            std::reverse(path.begin(), path.end());
            debugPrint("AStar::findPathOneStep: FOUND PATH!");
            return path;
        }

        closedNodes.insert(currentNode);

        for (Node* neighbour : currentNode->neighbours) {
            if (neighbour == nullptr) {
                continue;
            }
            
            if (closedNodes.find(neighbour) != closedNodes.end() || neighbour->getNodeType() == NODE_WALL) {
                continue;
            }
            
            float tentativeGCost = currentNode->gCost + heuristic(currentNode, neighbour);
            
            if (tentativeGCost < neighbour->gCost) {
                debugPrint("MAIN LOOP" + std::to_string(tentativeGCost));
                neighbour->parent = currentNode;
                neighbour->gCost = tentativeGCost;
                neighbour->hCost = heuristic(neighbour, goalNode);

                if (openNodesSet.find(neighbour) == openNodesSet.end()) { // Check using set
                    openNodes.push(neighbour);
                    openNodesSet.insert(neighbour); // Add to set
                }
            }
        }
    }


    debugPrint("AStar::findPathOneStep: DIDNT FIND PATH!");
    return std::vector<Node*>();
}
    



float AStar::heuristic(const Node *a, const Node *b)
{
    return std::abs(a->getPosition().x - b->getPosition().x) + std::abs(a->getPosition().y - b->getPosition().y);
}


