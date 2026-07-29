#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
sf::RectangleShape createRectangle(sf::Vector2f size, sf::Color color);
sf::CircleShape createCircle(float radius, sf::Color color);

/* Known issues
1. If the cube in the centers y value is smaller than left or right side
    the side rects will shrink as they collide at the top.
    solution??? if cube y value is less than l/r side y value subtract half
    the difference from the winy value.
2.
*/

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    sf::View view(sf::FloatRect({0, 0}, {800, -600}));
    window.setFramerateLimit(144);
    view.setCenter({0, 0});
    sf::Clock clock;

    float winX = 800;
    float winY = 600;

    sf::Vector2f rectSize = {50.f, 100.f};


    // Shapes
    sf::RectangleShape playerLeft = createRectangle(rectSize, sf::Color::Green);
    sf::RectangleShape playerRight = createRectangle({50.f, 100.f}, sf::Color::Red);
    sf::RectangleShape ball = createRectangle({50.f, 50.f}, sf::Color::Cyan);
    
    // Starting positions for rectangle. (Corner)
    float startX = (-winX / 2) + (ball.getSize().x / 2);
    float startY = (-winY / 2) + (ball.getSize().y / 2);
    float endX = (winX / 2) - (ball.getSize().x / 2);
    float endY = (winY / 2) - (ball.getSize().y / 2);

    // slope of line y = mx + b
    float transformSlopeX = 0;
    float transformSlopeY = 0;
    float m = (endY - startY - transformSlopeY) / (endX - startX - transformSlopeX);
    float b = startY - (startX * m);
    float rx = startX;
    float rSpeed = 200.f;
    rx = 0;

    // Start the window loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float dt = clock.restart().asSeconds();
        // Clear screen
        window.clear(sf::Color::White);
        window.setView(view);

    // Physics


        // Movement of ball
        // have rx constantly update and ry update based on rx
        rx = rx + rSpeed * dt;
        float ry = (rx * m) + b;


        // Collision checking between ball and boundaries.
        if (rx < startX || rx > endX)
        {
            rSpeed = -rSpeed;
            m = -m;
            b = ry - (rx * m);
        }
        if (ry < startY || ry > endY)
        {
            m = -m;
            b = ry - (rx * m);
        }

        // Collision checking of player and ball
        // if distance from origin of left/right rectangle and the origin of the ball is less than half the width
        // then there is a collison and flip the signs

            // Left player
        if (startX + (ball.getSize().x) >= rx)
        {
            rSpeed = -rSpeed;
            m = -m;
            b = ry - (rx * m);
        }
            // Right Player
        if(endX - (ball.getSize().x) <= rx)
        {
            rSpeed = -rSpeed;
            m = -m;
            b = ry - (rx * m);
        }

        ball.setPosition({rx, ry});
        playerLeft.setPosition({startX, ry});
        playerRight.setPosition({endX, ry});
        
        // check for key press up or down.
        

        // Movement of left player up and down.
        if (ry < startY || ry > endY)
        {
            playerLeft.setPosition({startX, ry});
        }
        // Movement of rig
        if (ry < startY || ry > endY)
        {
            playerRight.setPosition({endX, ry});
        }

        std::cout << "X: " << rx << " Y: " << ry << " M: " << m << " B: " << b << "         " << ry << " = " << m << "(" << rx << ")" << " + " << b << std::endl;

        // Render
        window.draw(playerLeft);
        window.draw(playerRight);
        window.draw(ball);
        window.display();
    }
}

sf::CircleShape createCircle(float radius, sf::Color color)
{
    sf::CircleShape circle(radius);
    circle.setOrigin({circle.getRadius(), circle.getRadius()});
    circle.setFillColor(color);

    return circle;
}

sf::RectangleShape createRectangle(sf::Vector2f size, sf::Color color)
{
    sf::RectangleShape rectangle(size);
    sf::Vector2f setGeometricCenter(size.x / 2.0f, size.y / 2.0f); // set origin of object to center
    rectangle.setOrigin(setGeometricCenter);
    rectangle.setFillColor(color);
    return rectangle;
}

/*Calculate change in X
           float currentX = cos(totalTime * frequency) * amplitude;
           float lastX = cos((totalTime - dt) * frequency) * amplitude;
           float xOffset = currentX - lastX;

           // Calculate change in Y
           float currentY = sin(totalTime * frequency) * amplitude;
           float lastY = sin((totalTime - dt) * frequency) * amplitude;
           float yOffset = currentY - lastY; */