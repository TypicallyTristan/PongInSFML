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

    sf::Vector2f rectSize = {200.f, 100.f};
    float totalTime = 0.f;
    float xSpeed = 150.f;
    float amplitude = 100.f;
    float frequency = 5.f;
    float radius = 100.f;

    float angle = 0.f;
    sf::RectangleShape playerLeft = createRectangle({50.f, 100.f}, sf::Color::Green);
    sf::RectangleShape rectangle = createRectangle(rectSize, sf::Color::Red);
    sf::RectangleShape rect2 = createRectangle({50.f, 50.f}, sf::Color::Cyan);
    sf::CircleShape circle = createCircle(radius, sf::Color::Red);
    sf::RectangleShape rectangle2 = createRectangle(rectSize, sf::Color::Red);
    sf::CircleShape circle2 = createCircle(radius, sf::Color::Green);

    // Starting positions for rectangle. (Corner)
    float startX = (-winX / 2) + (rect2.getSize().x / 2);
    float startY = (-winY / 2) + (rect2.getSize().y / 2);
    float endX = (winX / 2) - (rect2.getSize().x / 2);
    float endY = (winY / 2) - (rect2.getSize().y / 2);

    // slope of line
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
        float totalTime = totalTime + dt;

        // Move a circle about the origin 0,0

        // Constantly update theta
        float angle = angle + dt;

        // Calculate change in x
        float x = radius * cos(angle);

        // Calculate change in y
        float y = radius * sin(angle);

        // Movement of ball
        // have rx constantly update and ry update based on rx
        rx = rx + rSpeed * dt;
        float ry = (rx * m) + b;

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

        // if distance from origing of left rectangs is less than half the width
        // then there is a collison and flip the signs

        if (startX + (rect2.getSize().x) >= rx)
        {
            rSpeed = -rSpeed;
            m = -m;
            b = ry - (rx * m);
        }

        rect2.setPosition({rx, ry});
        playerLeft.setPosition({startX, ry});
        if (ry < startY || ry > endY)
        {
            playerLeft.setPosition({startX, ry});
        }

        std::cout << "X: " << rx << " Y: " << ry << " M: " << m << " B: " << b << "         " << ry << " = " << m << "(" << rx << ")" << " + " << b << std::endl;

            // Apply Physics
            // rectangle.setPosition({x, y});
            circle2.setPosition({x, y});
        circle.move(sf::Vector2f(x, y));
        rectangle.rotate(sf::degrees((x + y) * dt));

        // Render
        window.draw(playerLeft);
        window.draw(rectangle);
        window.draw(rect2);
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