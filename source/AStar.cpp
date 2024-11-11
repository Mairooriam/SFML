#include "AStar.hpp"
#include "priorityQueue.hpp"

bool AStar::debugEnabled = true; // Define the static member
void AStar::initAStar(Node *startNode, Node *goalNode)
{   
    this->goalNode = goalNode;
    startNode->gCost=0;
    startNode->hCost = heuristic(startNode,goalNode);
    startNode->updateTextString();
    openNodesSet.insert(startNode); // Add to set
    openNodes.push(startNode);
}

std::vector<Node *> AStar::findPathOneStep()
{
    std::cout << " OPEN NODES AT START: \n";
    printOpenNodes();
    enableDebug();
    if (!openNodes.empty()) {
        currentNode = openNodes.top();
        openNodes.pop();
        openNodesSet.erase(currentNode); // Remove from set

        if (currentNode == goalNode) {
            while (currentNode != nullptr) {
                currentNode->setColor(sf::Color::Blue);
                path.push_back(currentNode);
                currentNode = currentNode->parent;
                
            }
            std::reverse(path.begin(), path.end());
            debugPrint("AStar::findPathOneStep: FOUND PATH!");
            return path;
        }
        debugPrint("CLOSING NODE: " + currentNode->toString());
        closedNodes.insert(currentNode);
        currentNode->setColor(sf::Color::Blue);
        for (Node* neighbour : currentNode->neighbours) {
            if (neighbour == nullptr) {
                debugPrint("AStar::findPathOneStep: Neighbour is nullprt!");
                continue;
            }
            
            if (closedNodes.find(neighbour) != closedNodes.end() || neighbour->getNodeType() == NODE_WALL) {
                debugPrint("AStar::findPathOneStep: Neighbour is CLOSED OR WALL!" + neighbour->toString());
                continue;
            }
            
            float tentativeGCost = currentNode->gCost + heuristic(currentNode, neighbour);
            
            if (tentativeGCost < neighbour->gCost) {
                debugPrint("MAIN LOOP TENT GCOST" + std::to_string(tentativeGCost)+ "ON NODE: " + std::to_string(neighbour->getPosition().x) +"," + std::to_string(neighbour->getPosition().y));
                neighbour->parent = currentNode;
                neighbour->gCost = tentativeGCost;
                neighbour->hCost = heuristic(neighbour, goalNode);

                if (openNodesSet.find(neighbour) == openNodesSet.end()) { // Check using set
                    neighbour->setColor(sf::Color::Cyan);
                    neighbour->updateTextString();
                    openNodes.push(neighbour);
                    openNodesSet.insert(neighbour); // Add to set
                }
            }
        }
        debugPrint("AStar::findPathOneStep: OPENNODES END");

        printOpenNodes();
        
    }


    debugPrint("AStar::findPathOneStep: DIDNT FIND PATH!\n\n");
    return std::vector<Node*>();
}

void AStar::resetPathFinder()
{
    goalNode = nullptr; // Reset the goalNode pointer to nullptr
    openNodes = PriorityQueue<Node*>(); // Reinitialize the priority queue to an empty one
    openNodesSet.clear(); // Clear the unordered set
    closedNodes.clear(); // Clear the unordered set
}

int AStar::heuristic(const Node* a, const Node* b) {
    float scale = 10.0;
    float dx = std::abs(a->getPosition().x*scale - b->getPosition().x*scale);
    float dy = std::abs(a->getPosition().y*scale - b->getPosition().y*scale);
    return dx + dy + (std::sqrt(2) - 2) * std::min(dx, dy);
}


