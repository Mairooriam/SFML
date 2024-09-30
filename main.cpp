#include <SFML/Graphics.hpp>
#include <iostream>

#include "ball.h"

int main()
{
    
    // Output to console for verification
    std::cout << "Starting SFML application..." << std::endl;

    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window with Shape");

    // Create a vector to store Ball instances
    std::vector<Ball> balls;

    const int START_X = 0;
    const int START_Y = 0;
    const int OFFSET_MULTIPLIER = 10;
    // Create multiple Ball instances and add them to the vector
    for (size_t offset = 0; offset < 5; offset+=5) {
        balls.emplace_back(25, START_X + offset * OFFSET_MULTIPLIER , START_Y + offset * OFFSET_MULTIPLIER); // Adjust position for each ball
    }
    

    // Main loop
    sf::Clock clock;
    const float G_VELOCITY = 9.81f;
    float pos = 0;
    float speed = 0;
    
    while (window.isOpen())
    {

        sf::Time elapsed = clock.getElapsedTime();
        
        // 1 second refresh
        if (elapsed.asSeconds() > 1)
        {   
            if (pos < 600){ 
                speed += G_VELOCITY;
                pos += speed;
                balls[0].move(0, pos);
            }
            else{
                pos = 0;
            }
            
            std::cout << "time: " << elapsed.asSeconds() << " seconds\n" << "pos:" << pos << "speed:"<< speed << "\n";
            clock.restart();
        }
        
        
   
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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

    return 0;
}