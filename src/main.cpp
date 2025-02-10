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

            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    if (mouseMoved->position.x >= 0 && mouseMoved->position.x < window.getSize().x &&
                        mouseMoved->position.y >= 0 && mouseMoved->position.y < window.getSize().y) {
                        // get the current mouse position in the window
                        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                        // convert it to world coordinates
                        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                        drawingEngine.Draw(worldPos);
                    }
                }
            }

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                float screenW = 800.f;
                float screenH = 600.f;

                sf::Vector2u size = window.getSize();

                float heightR = screenH / screenW;
                float widthR = screenW / screenH;

                if (size.y * widthR <= size.x) {
                    size.x = size.y * widthR;
                }
                else if (size.x * heightR <= size.y) {
                    size.y = size.x * heightR;
                }
                
                window.setSize(size);
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