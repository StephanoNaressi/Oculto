#include <iostream>
#include <SFML/Graphics.hpp>
#include "DrawingEngine.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");
    Oculto::DrawingEngine drawingEngine;
    sf::Event event;
    sf::View view = window.getDefaultView();
    // Start the game loop
    while (window.isOpen())
    {

        // Process events
        while (window.pollEvent(event))
        {
            switch (event.type) {
                // Close window: exit
                case sf::Event::Closed:
                    window.close();
                    break;
                    case sf::Event::MouseMoved:
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

                            if (localPosition.x >= 0 && localPosition.x < window.getSize().x &&
                                localPosition.y >= 0 && localPosition.y < window.getSize().y) {
                                // get the current mouse position in the window
                                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                                // convert it to world coordinates
                                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                                drawingEngine.Draw(worldPos);
                            }
                        }
                    break;
                    case sf::Event::Resized:
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
                        break;

            }
        }

        // Clear screen
        window.clear();
        // Draw here

        //Draw your buffer
        window.draw(drawingEngine.GetMainSprite());

        // Update the window
        window.display();

    }

    return 0;
}