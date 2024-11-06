#include "game.hpp"

bool Game::debugEnabled = false; // Define the static member


Game::Game() : window(sf::VideoMode(800, 600), "SFML Game"),
    worldScale(std::make_shared<int>(128))
    //pathfinder(this->startNode, this->endNode)
    {
    // TODO: add calc into initmap to size/16 to get multiplier to scale sprite accordingly
    this->initMap(40);
    //this->updateMapScale();
    this->populateNodeNeighbours();
    
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleMouseEvent(event);
            handleKeyEvent(event);

        }
       
        // Update game logic here
        // For example, you can call a method to update the game state
        update(sf::seconds(1.f / 60.f));

        window.clear();
        // Render the game here
        drawMap();
        window.display();
    }
}
void Game::handleMouseEvent(sf::Event &event)
{
     // Check mouse button state continuously
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            map[mousePosWorld.x][mousePosWorld.y].printNeighbours();
            map[mousePosWorld.x][mousePosWorld.y].setNodeWall();
            debugPrint("Clicked at" + std::to_string(mousePosWorld.x) + std::to_string(mousePosWorld.y));
            // Use getNodePointer to get a pointer to the Node and add it to the map
            this->addNodeToCurrentlyWallNodesMap(map[mousePosWorld.x][mousePosWorld.y].getNodePointer());

    }
    enableDebug();
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            debugPrint("Game::handleMouseEvent: Left Mouse Button Pressed [(" + std::to_string(mousePosWindow.x) + ", " + std::to_string(mousePosWindow.y) + "),("  + std::to_string(mousePosWorld.x) + ", " + std::to_string(mousePosWorld.y) + ")]");

            
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            debugPrint("Game::handleMouseEvent: Right Mouse Button Pressed");
            
            // Handle right mouse button press
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            debugPrint("Game::handleMouseEvent: Left Mouse Button Released");
            
            // Handle left mouse button release1
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            debugPrint("Game::handleMouseEvent: Right Mouse Button Released");
            
            map[mousePosWorld.x][mousePosWorld.y].printNeighbourBitSet();
            map[mousePosWorld.x][mousePosWorld.y].updateTextAccordingToSpriteSize();
            this->printCurrentlyWallNodesMap();
            this->updateCurrentlyWallNodes();
            // Handle right mouse button release
        }
    disableDebug();
    } else if (event.type == sf::Event::MouseMoved) {
        updateMousePos(event.mouseMove.x,event.mouseMove.y);
        //map[mousePosWorld.x][mousePosWorld.y].cycleTextures();
        
        //debugPrint("Game::handleMouseEvent: Mouse Moved to [(" + std::to_string(mousePosWindow.x) + ", " + std::to_string(mousePosWindow.y) + "),("  + std::to_string(mousePosWorld.x) + ", " + std::to_string(mousePosWorld.y) + ")]");
        // Handle mouse move
    }
}
void Game::handleKeyEvent(sf::Event &event)
{
    enableDebug();
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::E:
                
                *worldScale += 5;
                updateMapScale();
                debugPrint("Game::handleKeyEvent: E Key Pressed. worldScale = [" + std::to_string(*worldScale)+"]" );
                break;
            case sf::Keyboard::Q:
                *worldScale -= 5;
                updateMapScale();
                debugPrint("Game::handleKeyEvent: Q Key Pressed. worldScale = [" + std::to_string(*worldScale)+"]" );
            break;
            case sf::Keyboard::W:
                *mapOffsetY -= 5;
                updateMapOffset();
                debugPrint("Game::handleKeyEvent: W Key Pressed");
                break;
           
            case sf::Keyboard::S:
                *mapOffsetY += 5;
                updateMapOffset();
                debugPrint("Game::handleKeyEvent: S Key Pressed");
                break;
            case sf::Keyboard::A:
                *mapOffsetX -= 5;
                updateMapOffset();
                debugPrint("Game::handleKeyEvent: A Key Pressed");
                break;
           
            case sf::Keyboard::D:
                *mapOffsetX += 5;
                updateMapOffset();
                debugPrint("Game::handleKeyEvent: D Key Pressed");
                break;
             case sf::Keyboard::G:
                printMap();
                debugPrint("Game::handleKeyEvent: G Key Pressed");
                break;
            case sf::Keyboard::Num1:
                startNode = map[mousePosWorld.x][mousePosWorld.y].getNodePointer();
                startNode->setColor(sf::Color::Cyan);
                debugPrint("Game::handleKeyEvent: 1 Key Pressed: Set Starting node!");
                break;
            case sf::Keyboard::Num2:
                endNode = map[mousePosWorld.x][mousePosWorld.y].getNodePointer();
                endNode->setColor(sf::Color::Red);
                debugPrint("Game::handleKeyEvent: 2 Key Pressed: Set End node!");
                break;
            case sf::Keyboard::Num3:
                map[mousePosWorld.x][mousePosWorld.y].updateAStarValues();
                
                debugPrint("Game::handleKeyEvent: 3 Key Pressed: Updated AStar values!");
                break;
             case sf::Keyboard::Num4:
                map[mousePosWorld.x][mousePosWorld.y].nodeType = NODE_EMPTY;
                map[mousePosWorld.x][mousePosWorld.y].setTextureRect(resourceManager.getTextureRect(FLOOR_GREEN,16,8,8));
                
                debugPrint("Game::handleKeyEvent: 4 Key Pressed: Updated NodeType to empty!");
                break;
            case sf::Keyboard::Num5:
                map[1][1].neighbours[tempDebugthingy]->cycleTextures();

                
                debugPrint("Game::handleKeyEvent: 5 Key Pressed: Cycling texture neigbour textures of (1,1) at:" + std::to_string(tempDebugthingy) );
                break;
            case sf::Keyboard::Num6:
                tempDebugthingy += 1;
                
                debugPrint("Game::handleKeyEvent: 6 Key Pressed: tempdebug tingy added!");
            break;
            case sf::Keyboard::Space:
                if (startNode && endNode)
                {
                    //pathfinder.findPathOneStep();
                    resetMapAstarValues();
                    pathfinder.initAStar(startNode,endNode);
                    std::vector<Node*> path = pathfinder.findPathOneStep();
                    for (auto &&node : path)
                    {
                        node->setColor(sf::Color::Black);
                    }
                    
                    
                    debugPrint("Game::handleKeyEvent: SPACE Key Pressed: pathfinder RAN");
                }else
                {
                    debugPrint("Game::handleKeyEvent: SPACE Key Pressed: pathfinder DIDNT run");
                }
                
                
                
            break;
            case sf::Keyboard::Escape:
                debugPrint("Game::handleKeyEvent: Escape Key Pressed");
                break;
            default:
                debugPrint("Game::handleKeyEvent: Other Key Pressed");
                break;
        }
    disableDebug();   
    } else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::W:
                debugPrint("Game::handleKeyEvent: W Key Pressed");
                //view.move(0, -10); // Pan up
                break;
            case sf::Keyboard::A:
                debugPrint("Game::handleKeyEvent: A Key Pressed");
                //view.move(-10, 0); // Pan left
                break;
            case sf::Keyboard::S:
                debugPrint("Game::handleKeyEvent: S Key Pressed");
                //view.move(0, 10); // Pan down
                break;
            case sf::Keyboard::D:
                debugPrint("Game::handleKeyEvent: D Key Pressed");
                //view.move(10, 0); // Pan right
                break;
            case sf::Keyboard::Q:
                debugPrint("Game::handleKeyEvent: Q Key Pressed");
                //view.zoom(1.1f); // Zoom out
                break;
            case sf::Keyboard::E:
                debugPrint("Game::handleKeyEvent: E Key Pressed");
                //view.zoom(0.9f); // Zoom in
                break;
            case sf::Keyboard::Escape:
                debugPrint("Game::handleKeyEvent: Escape Key Released");
                // Handle Escape key release
                break;
            default:
                debugPrint("Game::handleKeyEvent: Other Key Released");
                // Handle other key releases
                break;
        }
    }
}

void Game::updateMousePos(int x, int y)
{
    this->mousePosWindow.x = x;
    this->mousePosWindow.y = y;

    
    this->mousePosWorld.x = (x - *mapOffsetX) / *worldScale;
    this->mousePosWorld.y = (y - *mapOffsetY) / *worldScale;
}
void Game::updateCurrentlyWallNodes()
{
    enableDebug();
    for (auto& pair : currentlyWallNodesMap) {
        pair.second->updateNeighbourBitSet();
        pair.second->updateWallTextureAccordingToNeighbours();

        
    }
    
    debugPrint("UPDATED WALLS ACCORDING TO NEIGHKKBVOURS");
    disableDebug();
}
void Game::update(sf::Time deltaTime)
{
    // Update game state here
    // For example, you can update the positions of game objects
}
Node &Game::getNodeAtPosition()
{
    // TODO: insert return statement here
}
void Game::updateMapScale()
{
    for (size_t i = 0; i < map.size(); ++i) { // Use size() to get the number of rows
        for (size_t j = 0; j < map[i].size(); ++j) { // Use size() to get the number of columns
            // Assuming Node has a draw method that takes a window reference
            map[i][j].updateSpriteScale(*worldScale);
  
            //map[i][j].updateTextAccordingToSpriteSize();
            //map[i][j].updateSpritePosition();
        }
    }
}
void Game::updateMapOffset()
{
    for (size_t i = 0; i < map.size(); ++i) { // Use size() to get the number of rows
        for (size_t j = 0; j < map[i].size(); ++j) { // Use size() to get the number of columns
            // Assuming Node has a draw method that takes a window reference
            map[i][j].updateSpritePositionAccordingToOffset();
  
            //map[i][j].updateTextAccordingToSpriteSize();
            //map[i][j].updateSpritePosition();
        }
    }
}
void Game::resetMapAstarValues()
{
    for (size_t i = 0; i < map.size(); ++i) { 
        for (size_t j = 0; j < map[i].size(); ++j) {
            map[i][j].gCost = INFINITY;
            map[i][j].isVisited = false;
            //map[i][j].nodeType = NODE_EMPTY;
            map[i][j].parent = nullptr;
        }
    }
}
void Game::initMap(size_t mapSize)
{
    
    for (size_t i = 0; i < mapSize; ++i) {
        std::vector<Node> row;
        for (size_t j = 0; j < mapSize; ++j) {
            row.emplace_back(sf::Vector2f(i, j), resourceManager.getFont("arial"),resourceManager.createSprite16x16("wall_textures",FLOOR_GREEN), this);
        }
    map.push_back(row);
    }
}

void Game::populateNodeNeighbours()
{
    for (size_t i = 0; i < map.size(); ++i) { 
        for (size_t j = 0; j < map[i].size(); ++j) {
            Node* left = (i > 0) ? &map[i - 1][j] : nullptr;
            Node* top = (j > 0) ? &map[i][j - 1] : nullptr;
            Node* bottom = (j < map[i].size() - 1) ? &map[i][j + 1] : nullptr;
            Node* right = (i < map.size() - 1) ? &map[i + 1][j] : nullptr;

            Node* topLeft = (i > 0 && j > 0) ? &map[i - 1][j - 1] : nullptr;
            Node* bottomLeft = (i > 0 && j < map[i].size() - 1) ? &map[i - 1][j + 1] : nullptr;
            Node* topRight = (i < map.size() - 1 && j > 0) ? &map[i + 1][j - 1] : nullptr;
            Node* bottomRight = (i < map.size() - 1 && j < map[i].size() - 1) ? &map[i + 1][j + 1] : nullptr;

            map[i][j].updateNeighbours(top, left, right, bottom,
                                       topLeft, topRight, bottomLeft, bottomRight);
        }
    }
}
void Game::drawMap() {
    for (size_t i = 0; i < map.size(); ++i) { // Use size() to get the number of rows
        for (size_t j = 0; j < map[i].size(); ++j) { // Use size() to get the number of columns
            // Assuming Node has a draw method that takes a window reference
            map[i][j].draw(window);
        }
    }

    
    //std::cout << "DRAWING MAP\n" << "map size: " << map.size() << "\n" ;
}

sf::RenderWindow &Game::getRenderWindow()
{
    return this->window;
}

std::vector<std::vector<Node>> &Game::getMap()
{
    return this->map;
}



void Game::printMap() {

    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            // Assuming Node has a method to get its position or relevant information
            map[i][j].printNodeInfo();
        }
    }
}


void Game::addNodeToCurrentlyWallNodesMap(Node* node)
{
    this->currentlyWallNodesMap[node->getPosition()] = std::move(node);
}


void Game::printCurrentlyWallNodesMap() const {
    for (const auto& pair : currentlyWallNodesMap) {
        debugPrint("Key: (" + std::to_string(static_cast<int>(pair.first.x)) + ", " + std::to_string(static_cast<int>(pair.first.y)) + ") -> Value: " + pair.second->toString());
    }
}
void Game::setWorldScale(int newScale) {
    *worldScale = newScale; // Dereference and assign a new value
}