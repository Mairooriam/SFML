#include "Game.h"

#include <iostream>
#include "vectorOperators.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Window with Shape"),
      view(sf::FloatRect(0, 0, 800, 600)) {
    
    // intialize font
    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cerr << "Error loading font\n";
    }
    initButtons();
    initMap(10,sf::Vector2f(100,100));
    // creating balls and initial values for them
    const sf::Vector3f initialVelocity(0.0f, 0.0f, 0.0f);
    sf::Vector3f position(0.0f, 0.0f,0.0f);
    for (size_t offset = 0; offset < 1; offset++) {
        balls.emplace_back(5, position, initialVelocity);
    }

    // Debug window init
    debugOverlay.addTextField("Time Elapsed: ", std::to_string(totalElapsedTime.asSeconds()));
    debugOverlay.addTextField("Ball 1 x: ", std::to_string(balls[0].position.x) + "Y: " + std::to_string(balls[0].position.y) + "Z: " + std::to_string(balls[0].position.z));
    



    // Instead of setting the size, use zoom to zoom out
    //view.zoom(1.0f); // Zoom out by a factor of 2 (0.5 means zoom out)
    window.setView(view);
}

void Game::initButtons()
{
    // Initialize buttons and add them to the vector
    buttons.emplace_back(100.0f,100.0f,150.0f,50.0f,&font,"button 1", sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta);
    sf::FloatRect boundingBox = buttons[0].button.getGlobalBounds();
    std::cout << "Bounding Box: " << boundingBox.left << ", " << boundingBox.top << ", " << boundingBox.width << ", " << boundingBox.height << std::endl;
    std::cout << "button0 pos" << buttons[0].getPosition() << "\n";
}

void Game::initMap(size_t mapSize, sf::Vector2f nodeSize)
{
    float offset = nodeSize.x + 5.0f;
    //map.emplace_back(1, 1, nodeSize, &font, std::to_string(1) + "," + std::to_string(1));
    for (size_t i = 0; i < mapSize; i++)
    {
        for (size_t j = 0; j < mapSize; j++)
        {
            map.emplace_back(j*offset, i*offset, nodeSize, &font, std::to_string(i) + "," + std::to_string(j));
        }
        
        
    }
    
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
    //const sf::Time TimePerFrame = sf::seconds(1.0f);
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        totalElapsedTime += deltaTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            mousePos = sf::Mouse::getPosition(window);
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(totalElapsedTime);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
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

void Game::update(sf::Time totalElapsedTime) {
    debugOverlay.updateTextField("Time Elapsed: ", std::to_string(totalElapsedTime.asSeconds()));
    debugOverlay.updateTextField("Ball 1 x: ", std::to_string(balls[0].position.x) + "Y: " + std::to_string(balls[0].position.y) + "Z: " + std::to_string(balls[0].position.z));
    
    for (auto& ball : balls) {
        if(!ball.update(totalElapsedTime.asSeconds())){
            totalElapsedTime = sf::seconds(0);
        };
    }

    for (auto& button : buttons){
         button.update(mousePos);
    }

     for (auto& node : map){
        node.update(mousePos);
    }

}

void Game::render() {
    window.clear();

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
    for (auto& node : map)
    {
        node.draw(window, sf::RenderStates::Default);
    }
    
    debugOverlay.draw(window);
    window.display();
}


