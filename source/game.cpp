#include "game.hpp"

bool Game::debugEnabled = false; // Define the static member
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;
Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game"),
    worldScale(std::make_shared<int>(128))
    {
    // TODO: add calc into initmap to size/16 to get multiplier to scale sprite accordingly
    this->initMap(25);
    //this->updateMapScale();
    this->populateNodeNeighbours();
    
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f); // 60Hz

    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                handleMouseEvent(event);
                handleKeyEvent(event);
            }

            // Update game logic here
            update(TimePerFrame);
        }

        window.clear();
        // Render the game here
        drawMap();
        drawMapText();
        window.display();
    }
}
void Game::handleMouseEvent(sf::Event &event)
{
     // Check mouse button state continuously
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            
            map[mousePosWorld.x][mousePosWorld.y].printNeighbours();
            map[mousePosWorld.x][mousePosWorld.y].setNodeWall();
            //debugPrint("Clicked at" + std::to_string(mousePosWorld.x) + std::to_string(mousePosWorld.y));
            // Use getNodePointer to get a pointer to the Node and add it to the map
            this->addNodeToCurrentlyWallNodesMap(map[mousePosWorld.x][mousePosWorld.y].getNodePointer());

    }else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    {
        if (!isMiddleMousePressed) {
            // Middle mouse button pressed for the first time
            mousePosTemp = sf::Vector2f(mousePosWindow.x, mousePosWindow.y);
            isMiddleMousePressed = true;
        } else {
            // Middle mouse button is held down
            sf::Vector2f newPositon(mousePosWindow.x, mousePosWindow.y);
            debugPrint("old pos:" + std::to_string(mousePosTemp.x) + std::to_string(mousePosTemp.y));
            debugPrint("new pos:" + std::to_string(newPositon.x) + std::to_string(newPositon.y));
            
            sf::Vector2f delta = newPositon - mousePosTemp;
            debugPrint("calculated delta: " + std::to_string(delta.x) + std::to_string(delta.y));

            *mapOffsetX += delta.x; // Move in the x direction based on delta
            *mapOffsetY += delta.y; // Move in the y direction based on delta

            mousePosTemp = newPositon; // Update the temporary mouse position
            updateMapOffset();
        }
    } else {
        // Reset the flag when the middle mouse button is released
        isMiddleMousePressed = false;
    }
     

    if (event.type == sf::Event::MouseWheelMoved){
            debugPrint("Game::handleMouseEvent: scrolled");
            if (event.mouseWheel.delta <= 0)
            {
                *worldScale -= 5;
            }else{
                *worldScale += 5;
            }
            
            
            updateMapScale();
        }  
    enableDebug();
    if (event.type == sf::Event::MouseButtonPressed) {
        mouseOneDown = true;
        if (event.mouseButton.button == sf::Mouse::Left) {
            debugPrint("Game::handleMouseEvent: Left Mouse Button Pressed [(" + std::to_string(mousePosWindow.x) + ", " + std::to_string(mousePosWindow.y) + "),("  + std::to_string(mousePosWorld.x) + ", " + std::to_string(mousePosWorld.y) + ")]");
            
            
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            debugPrint("Game::handleMouseEvent: Right Mouse Button Pressed");
            
            // Handle right mouse button press
        }
        else if (event.mouseButton.button == sf::Mouse::Middle){
            debugPrint("Game::handleMouseEvent: middlemouse pressed");
            //middleMouseDown = true;
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        mouseOneDown = false;
        if (event.mouseButton.button == sf::Mouse::Left) {
            updateCurrentlyWallNodes();
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
        // else if (event.mouseButton.button == sf::Mouse::Middle){
        //     debugPrint("Game::handleMouseEvent: middlemouse released");
        //     middleMouseDown = false;
        //     sf::Vector2f newPositon(event.mouseButton.x, event.mouseButton.y);
        //     debugPrint("old pos:" + std::to_string(mousePosTemp.x) + std::to_string(mousePosTemp.y));
        //     debugPrint("new pos:" + std::to_string(newPositon.x) + std::to_string(newPositon.y));
        //     mousePosTemp = mousePosTemp - newPositon;
        //     debugPrint("calculated delta: " + std::to_string(mousePosTemp.x) + std::to_string(mousePosTemp.y));

        //     *mapOffsetX -= mousePosTemp.x;
        //     *mapOffsetY -= mousePosTemp.y;
        //     updateMapOffset();
        // }
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
                if (startNode && endNode){
                    
                    pathfinder.initAStar(startNode,endNode);
                }
                debugPrint("Game::handleKeyEvent: G Key Pressed");
                break;
            case sf::Keyboard::C:
                resetMap();
                pathfinder.resetPathFinder();
                debugPrint("Game::handleKeyEvent: C Key Pressed-> resetting map");
                break;
            case sf::Keyboard::Num1:
                if (startNode == nullptr){
                    startNode = map[mousePosWorld.x][mousePosWorld.y].getNodePointer();
                    startNode->setColor(sf::Color::Cyan);
                    debugPrint("Game::handleKeyEvent: 1 Key Pressed: Set Starting node!");
                }else{
                    debugPrint("Game::handleKeyEvent: 1 Key Pressed: There is already startNode!");
                }
                

                
                break;
            case sf::Keyboard::Num2:
                if (endNode == nullptr){
                    endNode = map[mousePosWorld.x][mousePosWorld.y].getNodePointer();
                    endNode->setColor(sf::Color::Red);
                    debugPrint("Game::handleKeyEvent: 2 Key Pressed: Set End node!");
                }else{
                    debugPrint("Game::handleKeyEvent: 2 Key Pressed: There is already endNode!");
                }
                
                break;
            case sf::Keyboard::Num3:
                
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
                    
                    
                    path = pathfinder.findPathOneStep(true);
                    if (path != std::vector<Node*>()){
                        animationON = true;
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
    
    //debugPrint("UPDATED WALLS ACCORDING TO NEIGHKKBVOURS");
    disableDebug();
}
void Game::update(sf::Time deltaTime)
{
    //disableDebug();
    accumulatedTime += deltaTime;
    //debugPrint("Game::update: accmulated" + std::to_string(accumulatedTime.asMilliseconds()) + "ms");
    //debugPrint("Game::update: accmulated" + std::to_string(accumulatedTime.asMilliseconds()) + "ms");
    //debugPrint("Game::update: deltatime" + std::to_string(deltaTime.asMilliseconds()) + "ms");
    // Check if one second has passed
    if (accumulatedTime >= sf::seconds(0.1f)) {
        //Perform actions that should run every second
        if (animationON)
        {
            drawPathAnimation();
        }
        
        

        // Reset the accumulated time
        accumulatedTime = sf::seconds(0.0f);
    }
    
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
void Game::resetMap()
{
    startNode = nullptr;
    endNode = nullptr;
    *mapOffsetX = 0;
    *mapOffsetY = 0;
    for (size_t i = 0; i < map.size(); ++i) { 
        for (size_t j = 0; j < map[i].size(); ++j) {
            map[i][j].gCost = INFINITY;
            map[i][j].hCost = INFINITY;
            map[i][j].isVisited = false;
            map[i][j].parent = nullptr;
            map[i][j].setNodeDefault();
            map[i][j].updateTextString();
            currentlyWallNodesMap.clear();
            

        }
    }
    updateMapScale();
    updateMapOffset();
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
    int drawingCounter = 0;
    for (size_t i = 0; i < map.size(); ++i) { // Use size() to get the number of rows
        for (size_t j = 0; j < map[i].size(); ++j) { // Use size() to get the number of columns
            // Assuming Node has a draw method that takes a window reference
            if(map[i][j].isVisible(WINDOW_WIDTH,WINDOW_HEIGHT)){
                map[i][j].draw(window);
                drawingCounter ++;
            }
        }
    }
    drawCallCount ++;
    //debugPrint("Game::drawMap: drawed:" + std::to_string(drawingCounter) + " nodes. DrawCallCount" + std::to_string(drawCallCount));
    
    
    //std::cout << "DRAWING MAP\n" << "map size: " << map.size() << "\n" ;
}

void Game::drawMapText()
{
    for (size_t i = 0; i < map.size(); ++i) { // Use size() to get the number of rows
        for (size_t j = 0; j < map[i].size(); ++j) { // Use size() to get the number of columns
            // Assuming Node has a draw method that takes a window reference
            map[i][j].drawText(window);
        }
    }
}

void Game::drawPathStep(Node* step)
{
    step->setNodePath();
}

void Game::drawPathAnimation()
{
    enableDebug();
    debugPrint("Game::drawPathAnimation : COUNTER: " + std::to_string(pathAnimationCounter) + "Path Size" + std::to_string(path.size()));

        if (pathAnimationCounter <= path.size() & path.size() > 0){
            debugPrint("Game::drawPathAnimation : Inisde counter incrimentr");
            path[pathAnimationCounter]->setNodePath();
            pathAnimationCounter += 1;
        }
        
        if(pathAnimationCounter == path.size())
        {
            debugPrint("Game:DrawPathAnimation: Animation done setting animation off");
            animationON = false;
            pathAnimationCounter = 0;
            for (size_t i = 0; i < path.size(); ++i) {
                path[i]->setColor(sf::Color::Magenta);
            }        
        }
   
}

void Game::drawPathFull(std::vector<Node *> &path)
{
    for (auto &&node : path)
    {
        node->setNodePath();

    }
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