#include <iostream>
#include <SFML/Graphics.hpp>
#include "DrawingEngine.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");
    Oculto::DrawingEngine drawingEngine;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
            //MousePressed testing
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    std::cout << "PRESSED LEFT" << std::endl;
                    drawingEngine.Draw(mouseButtonPressed->position);
                }
            }
        }

        // Clear screen
        window.clear();
        // Draw here

        //Draw your buffer
        window.draw(*(drawingEngine.GetMainSprite().get()));

        // Update the window
        window.display();
    }

    return 0;
}