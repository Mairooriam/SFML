#include "Game.hpp"
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <bitset>
//#include "enums.h"
#include "resourceManager.hpp"
#include "gameStateManager.hpp"
#include <queue>
#include <functional>
#include <iostream>

#include "node.hpp"


Game game;
int main() {
    // ResourceManager& resourceManager = ResourceManager::getInstance(); // Use Singleton instance

	// Node node1(sf::Vector2f(0,0), resourceManager.getFont("arial"),resourceManager.createSprite16x16("wall_textures",FLOOR_GREEN),&game);
	// Node node2(sf::Vector2f(1,0), resourceManager.getFont("arial"),resourceManager.createSprite16x16("wall_textures",FLOOR_GREEN),&game);;
	// Node node3(sf::Vector2f(0,1), resourceManager.getFont("arial"),resourceManager.createSprite16x16("wall_textures",FLOOR_GREEN),&game);;
	// node2.gCost = 10;
	// node1.gCost = 20;
	// node3.gCost = 30;
 
    Game game;
    
    game.run();


   
//  std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq;

//     // Add the Node objects to the priority queue
//     pq.push(&node1);
//     pq.push(&node2);
//     pq.push(&node3);

//     std::cout << "STARTING PRINTING" << "\n";
//     while (!pq.empty()) {
//         Node* node = pq.top();
//         std::cout << *node << std::endl; // Use the << operator
//         pq.pop();
//     }
      return 0;

   
}

