#include "Game.h"

#include <iostream>

Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Window with Shape"),
      view(sf::FloatRect(0, 0, 800, 600)) {
    const sf::Vector3f initialVelocity(0.0f, 0.0f, 0.0f);
    sf::Vector3f position(0.0f, 0.0f,0.0f);

    for (size_t offset = 0; offset < 5; offset++) {
        balls.emplace_back(50, position, initialVelocity);
    }

    
    // Instead of setting the size, use zoom to zoom out
    view.zoom(10.0f); // Zoom out by a factor of 2 (0.5 means zoom out)
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
            update(TimePerFrame);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(sf::Time totalElapsedTime) {
    for (auto& ball : balls) {
        if(!ball.update(totalElapsedTime.asSeconds())){
            totalElapsedTime = sf::seconds(0);
        };
    }
}

void Game::render() {
    window.clear();
    for (auto& ball : balls) {
        ball.draw(window);
    }
    window.display();
}