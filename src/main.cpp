#include <optional>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear();
        // Draw here
        // Creates a Pixel Image Buffer
        sf::Image buffer(sf::Vector2u(800, 600), sf::Color(255, 255, 255));
        //Set SRGB conversion to false? Maybe check
        sf::Texture texture(buffer, false);
        // Create a sprite from the texture
        sf::Sprite bufferSprite(texture);
        //Draw your buffer
        window.draw(bufferSprite);

        // Update the window
        window.display();
    }

    return 0;
}