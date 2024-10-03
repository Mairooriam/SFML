#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ball.h"

float kinematicEquation(float acceleration, float velocity, float deltaT, float position){
    float result = 0.5f * acceleration * deltaT * deltaT + velocity * deltaT + position;
        //std::cout << "kinematicEquation: " << result << "deltaT: " << deltaT << "\n";
        
        return result;
    };
int main() {
    // Output to console for verification
    std::cout << "Starting SFML application..." << std::endl;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window with Shape");

    // Create a vector to store Ball instances
    std::vector<Ball> balls;

    const int START_X = 0;
    const int START_Y = 0;
    const int OFFSET_MULTIPLIER = 10;
    const sf::Vector2f initialVelocity(0.0f, 0.0f);
    sf::Vector3f position(0.0f,0.0f,0.0f);
    // Create multiple Ball instances and add them to the vector
    for (size_t offset = 0; offset < 5; offset++) {
        balls.emplace_back(50, position, initialVelocity);
    }

    // Create a view and set its initial size
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // Scale the view (e.g., zoom in by a factor of 2)
    view.setSize(view.getSize().x * 20.0f, view.getSize().y * 20.0f);

    // Set the view to the window
    window.setView(view);

    
    // Variables for physics calculations
    float velocity = 0;
    float acceleration = 0;
    float deltaT = 0;
    const float GRAVITY = 9.8f; // Example gravity velocity
    //const float TIME_STEP = 1.0f; // 60.0f; // Fixed time step (60 updates per second)
    const float TIME_STEP = 1.0f / 60.0f;
    sf::Clock clock;
    float time = 0.0f;
    float frameCounter = 0.0f;
    while (window.isOpen()) {
        sf::Time frameTime = clock.restart();
        time += frameTime.asSeconds();
        frameCounter += frameTime.asSeconds();
        //std::cout << "frametime: " << frameTime.asSeconds() << " seconds, time: " << time << " seconds\n";
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Fixed time step loop for physics updates
        if (frameCounter >= TIME_STEP){
            // Update physics
            std::cout << "frameCounter: " << frameCounter << "\n";
            if (balls[0].getPosition().y < 6000) {
                position.x = balls[0].getPosition().x;
                position.y = balls[0].getPosition().y;
                float newBallX = kinematicEquation(0,initialVelocity.x,time,position.x);
                float newBallY = kinematicEquation(GRAVITY,initialVelocity.y,time,position.y);
                float newBallZ = 0.0f;
                //std::cout << "Physics ran" << "\n" << "x: "<< newBallX << "|" << "y: " << newBallY << "\n";
                balls[0].setPosition(newBallX,newBallY,newBallZ);
                std::cout << "Physics ran" << "\n" << "x: "<< newBallY << "\n";
            } else {
                balls[0].setPosition(0.0f,0.0f,0.0f);
                velocity = 0;

            }
            frameCounter = 0;
        }
        // Clear the window
            window.clear();

            // Draw all balls
            for (auto& ball : balls) {
                ball.draw(window);
            }

            // Display the contents of the window
            window.display();
    }


    std::cout << "Exiting SFML application..." << std::endl;

    // Wait for user input before closing the console
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}


