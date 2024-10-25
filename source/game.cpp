#include "Game.h"

#include <iostream>
#include "vectorOperators.h"
#include "debug.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Window with Shape"),
      view(sf::FloatRect(0, 0, 800, 600))
    {
    initFonts();
    initTextures();
    {
        //Timer timer("INIT MAP DURATION");
        initMap(20,sf::Vector2f(100,100),0.0f);
    }
    
    // creating balls and initial values for them
    const sf::Vector3f initialVelocity(0.0f, 0.0f, 0.0f);
    sf::Vector3f position(0.0f, 0.0f,0.0f);
    for (size_t offset = 0; offset < 1; offset++) {
        balls.emplace_back(5, position, initialVelocity);
    }
    // Instead of setting the size, use zoom to zoom out
    //view.zoom(1.0f); // Zoom out by a factor of 2 (0.5 means zoom out)
    {
        //Timer timer("INIT BUTTONS & DEBUGWINDOW DURATION");
        initButtons();
        initDebugWindow();
    }
    
    window.setView(view);
}




void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    //const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
    const sf::Time TimePerFrame = sf::seconds(1.0f);
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        totalElapsedTime += deltaTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            mousePos = sf::Mouse::getPosition(window);
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            {
            Timer timer("ONE UPDATE CYCLE");

            // Track memory usage before update
            size_t memoryBefore = MemoryTracker::getTotalAllocatedMemory();
            update(totalElapsedTime);

            // Track memory usage after update
            size_t memoryAfter = MemoryTracker::getTotalAllocatedMemory();

            std::cout << "Memory used by update: " << (memoryAfter - memoryBefore) << " bytes" << std::endl;
        
            }
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        processKeyPressed(&event);
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonReleased){
           
            std::cout << "clieck at X:" << mousePos.x << "Y:" << mousePos.y << "\n";
        }
        if(buttons[0].buttonState == 1){
            std::cout << "BUTTOM PRESSED" << "\n";
        }
        
    }
}

void Game::processKeyPressed(sf::Event *event)
{
    if (event->type == sf::Event::KeyPressed) {
        switch (event->key.code) {
            case sf::Keyboard::Num1:
                this->selectedHotkey = NODE_EMPTY;
                
                std::cout << "Button 1 pressed selected empty\n";
                break;
            case sf::Keyboard::Num2:
                this->selectedHotkey = NODE_PLAYER;
                std::cout << "Button 2 pressed selected player\n";
                break;
            case sf::Keyboard::Num3:
                this->selectedHotkey = NODE_ENEMY;
                std::cout << "Button 3 pressed Selected enemy\n";
                break;
            case sf::Keyboard::Num4:
                this->selectedHotkey = NODE_WALL;
                //map[1][1].printNeighbours();
                //map[1][1].isWall();
                map[1][1].printNeighbours();
                std::cout << "NEIGHBOUR BITSET: \n"<< map[1][1].areNeighboursWall() << "\n";
                std::cout << "Button 4 pressed, Selected WALL\n";
                break;
            case sf::Keyboard::Num5:
                //this->selectedHotkey = NODE_WALL_2;
                std::cout << "Button 5 pressed\n";
                break;
            case sf::Keyboard::Num6:
                //this->selectedHotkey = NODE_WALL_3;
                std::cout << "Button 6 pressed\n";
                break;
            case sf::Keyboard::Num7:
                //this->selectedHotkey = NODE_WALL_4;
                std::cout << "Button 7 pressed\n";
                break;
            case sf::Keyboard::Num8:
                std::cout << "Button 8 pressed\n";
                break;
            case sf::Keyboard::Num9:
                std::cout << "Button 9 pressed\n";
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time totalElapsedTime) {
    debugOverlay.updateTextField("Time Elapsed: ", std::to_string(totalElapsedTime.asSeconds()));
    debugOverlay.updateTextField("Ball 1 x: ", std::to_string(balls[0].position.x) + "Y: " + std::to_string(balls[0].position.y) + "Z: " + std::to_string(balls[0].position.z));
    debugOverlay.updateTextField("Selected tile: ", nodeTypeToString(selectedHotkey));
   
    for (auto& ball : balls) {
        if(!ball.update(totalElapsedTime.asSeconds())){
            totalElapsedTime = sf::seconds(0);
        };
    }

    for (auto& button : buttons){
         button.update(mousePos);
    };

    int checkNeighbourResult;
    for (auto& row : map){
        for (auto& node : row){
            int updateResult = node.update(mousePos,  selectedHotkey);
            switch (updateResult)
            {
                case NODE_WALL:
                    checkNeighbourResult = node.areNeighboursWall();
                    if ( checkNeighbourResult != 0 & node.isWall()){
                        //std::cout << "neikbour checkresult " << checkResult << "\n";
                        node.updateWallTextureAccordingToNeighbours(checkNeighbourResult);
                    }
                    break;
                
                default:
                    break;
            }
            

        }
    }
    // DEBUG FOR SINGLE NODE.
    // int checkResult = map[1][1].areNeighboursWall();
    // if ( checkResult != 0){
    //     //std::cout << "neikbour checkresult " << checkResult << "\n";
    //     map[1][1].updateWallTextureAccordingToNeighbours(checkResult);
    // }
}
void Game::updateWalls()
{
    for (auto& row : map){
        for (auto& node : row){
            int checkResult = node.areNeighboursWall();
            if ( checkResult != 0 & node.isWall()){
                node.updateWallTextureAccordingToNeighbours(checkResult);
            }
        }
    }
}


void Game::render() {
    window.clear(sf::Color::Blue);

    // Test rectangle delete later
    sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(100.f, 100.f);
    window.draw(rectangle);

    // Test line delete later
    sf::Vertex line[] =
    {
    sf::Vertex(sf::Vector2f(0, 0)),
    sf::Vertex(sf::Vector2f(500, 500))
    };
    window.draw(line, 2, sf::Lines);
    
    // Draw blls
    for (auto& ball : balls) {
        ball.draw(window);
    }

    //Draw buttons.
    for (auto& button : buttons){
        button.draw(window,sf::RenderStates::Default);
    }

    // Draw map
    
    for (auto& row : map){
        for (Node node : row){
            //node.draw(window, sf::RenderStates::Default);
            window.draw(node);
        }
    }

    // draw sprite
    sf::Sprite sprite;
    sprite.setTexture(textures[1]);
    sprite.setTextureRect(sf::IntRect(0,0,16,16));// Assuming textures[0] is the desired texture
    sprite.setPosition(250.f, 250.f); // Set the position of the sprite
    
    window.draw(sprite);
    debugOverlay.drawBackground(window);
    debugOverlay.draw(window);
    window.display();
}

// INIT STUFF

void Game::initMap(size_t mapSize, sf::Vector2f nodeSize, float offset)
{
    offset += nodeSize.x;
    for (size_t i = 0; i < mapSize; ++i) {
        std::vector<Node> row;
        for (size_t j = 0; j < mapSize; ++j) {
            row.emplace_back(j * offset, i * offset, nodeSize, &font, std::to_string(i) + "," + std::to_string(j), this->textures[1], &textures);
        }
        map.push_back(row);
    }

    // old
    // Populate neighbors
    // for (size_t i = 0; i < mapSize; ++i) {
    //     for (size_t j = 0; j < mapSize; ++j) {
    //         Node& currentNode = map[i][j];
    //         // Add neighbors (up, down, left, right)
    //         if (i > 0) currentNode.neighbors.push_back(&map[i - 1][j]); // Up
    //         if (i < mapSize - 1) currentNode.neighbors.push_back(&map[i + 1][j]); // Down
    //         if (j > 0) currentNode.neighbors.push_back(&map[i][j - 1]); // Left
    //         if (j < mapSize - 1) currentNode.neighbors.push_back(&map[i][j + 1]); // Right
    //     }
    // }

    // Populate neighbors
    for (size_t i = 0; i < mapSize; ++i) {
        for (size_t j = 0; j < mapSize; ++j) {
            Node& currentNode = map[i][j];
            // Add neighbors (up, down, left, right)
            currentNode.neighbors.push_back((i > 0) ? &map[i - 1][j] : nullptr); // Up
            currentNode.neighbors.push_back((i < mapSize - 1) ? &map[i + 1][j] : nullptr); // Down
            currentNode.neighbors.push_back((j > 0) ? &map[i][j - 1] : nullptr); // Left
            currentNode.neighbors.push_back((j < mapSize - 1) ? &map[i][j + 1] : nullptr); // Right
        }
    }
    MemoryTracker::trackAllocation(&map,sizeof(map));
    MemoryTracker::trackAllocation(&map[0][0].neighbors,sizeof(map[0][0].neighbors));
}

int Game::initFonts()
{
    // intialize font
    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }
    return 0;
}

int Game::initTextures()
{
    // Ensure the vector has the correct size
    textures.resize(2);

    if (!textures[0].loadFromFile("resources/kuva.png")) {
        // Handle loading error
        std::cerr << "Error loading Kissa texture\n";
        return -1;
    }

    if (!textures[1].loadFromFile("resources/wall_textures.png")) {
        // Handle loading error
        std::cerr << "Error loading SEINÄ texture\n";
        return -1;
    }

    return 0;
}

int Game::initDebugWindow()
{
    // Debug window init
    debugOverlay.addTextField("Time Elapsed: ", std::to_string(totalElapsedTime.asSeconds()));
    debugOverlay.addTextField("Ball 1 x: ", std::to_string(balls[0].position.x) + "Y: " + std::to_string(balls[0].position.y) + "Z: " + std::to_string(balls[0].position.z));
    debugOverlay.addTextField("Selected tile: ", nodeTypeToString(selectedHotkey));
    debugOverlay.drawBackground(window);
    return 0;
}

void Game::initButtons()
{
    // Initialize buttons and add them to the vector
    buttons.emplace_back(100.0f,100.0f,150.0f,50.0f,&font,"button 1", sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta);
    sf::FloatRect boundingBox = buttons[0].button.getGlobalBounds();
    std::cout << "Bounding Box: " << boundingBox.left << ", " << boundingBox.top << ", " << boundingBox.width << ", " << boundingBox.height << std::endl;
    std::cout << "button0 pos" << buttons[0].getPosition() << "\n";
}