#include "Game.h"

#include <iostream>
#include "vectorOperators.h"
Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Window with Shape"),
      view(sf::FloatRect(0, 0, 800, 600)) {
    const sf::Vector3f initialVelocity(0.0f, 0.0f, 0.0f);
    sf::Vector3f position(0.0f, 0.0f,0.0f);

    for (size_t offset = 0; offset < 1; offset++) {
        balls.emplace_back(5, position, initialVelocity, 10.0f);
    }

    debugOverlay.addTextField("Time Elapsed: ", std::to_string(totalElapsedTime.asSeconds()));
    debugOverlay.addTextField("Ball 1 x: ", std::to_string(balls[0].position.x) + "Y: " + std::to_string(balls[0].position.y) + "Z: " + std::to_string(balls[0].position.z));
    // Instead of setting the size, use zoom to zoom out
    //view.zoom(1.0f); // Zoom out by a factor of 2 (0.5 means zoom out)
    window.setView(view);
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
            sf::Vector2i position = mouse.getPosition(window);
            std::cout << "clieck at X:" << position.x << "Y:" << position.y << "\n";
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
}

void Game::render() {
    window.clear();


    sf::Vertex line[] =
    {
    sf::Vertex(sf::Vector2f(0, 0)),
    sf::Vertex(sf::Vector2f(500, 500))
    };

    window.draw(line, 2, sf::Lines);
    for (auto& ball : balls) {
        ball.draw(window);
    }
    debugOverlay.draw(window);
    window.display();
}