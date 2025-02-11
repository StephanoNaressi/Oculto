#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "DrawingEngine.hpp"



int main()
{
    constexpr unsigned MIN_WINDOW_WIDTH = 1400;
    constexpr unsigned MIN_WINDOW_HEIGHT = 600;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 1400, 600 }), "Oculto");
    tgui::Gui gui{ window };

    Oculto::DrawingEngine drawingEngine;
    //Color Picker
    auto colorPicker = tgui::ColorPicker::create("Choose a colour!", tgui::Color::Black);
    gui.add(colorPicker);
    colorPicker->setPosition(0, 0);
    colorPicker->setSize(tgui::bindWidth(gui) * 0.45f, tgui::bindHeight(gui));
    colorPicker->setPositionLocked(true);
    colorPicker->setResizable(false);
    //Child Objects
    auto& widgets = colorPicker->getWidgets();
    for (std::size_t i = widgets.size(); i-- > 0; ) {
        if (widgets[i]->getWidgetType() == "Button") {
            auto button = std::dynamic_pointer_cast<tgui::Button>(widgets[i]);

            if (button && (button->getText() == "Cancel" || button->getText() == "OK" || button->getText() == "Reset")) {
                colorPicker->remove(button);
            }
        }
    }
    //Widgets
    auto canvas = tgui::CanvasSFML::create({ 800,600 });
    gui.add(canvas);
    canvas->setSize(tgui::bindWidth(gui) * 0.55f, tgui::bindHeight(gui));
    canvas->setPosition(tgui::bindWidth(gui) * 0.45f, 0);

    // Start the game loop
    const sf::Vector2u initialWindowSize = window.getSize();

    // Resize handler lambda
    auto updateLayout = [&](unsigned width, unsigned height) {
        // Clamp to minimum size first
        width = std::max(width, MIN_WINDOW_WIDTH);
        height = std::max(height, MIN_WINDOW_HEIGHT);

        // Your existing layout calculations
        const float targetRatio = 4.0f / 3.0f;
        const float canvasWidth = std::min(width * 0.55f, height * targetRatio);
        const float canvasHeight = canvasWidth / targetRatio;

        canvas->setSize(canvasWidth, canvasHeight);
        canvas->setPosition(width - canvasWidth, (height - canvasHeight) / 2);
        drawingEngine.GetMainSprite().setScale(canvasWidth / 800.f, canvasHeight / 600.f);
        window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
        };
    updateLayout(1400, 600);

    while (window.isOpen())
    {
        sf::Event event;

        // Process events
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);

            switch (event.type) {
                // Close window: exit
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseMoved:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        const sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
                        const sf::Vector2f canvasPos = canvas->getAbsolutePosition();
                        const sf::Vector2f canvasSize = canvas->getSize();

                        if (mousePos.x >= canvasPos.x && mousePos.x <= canvasPos.x + canvasSize.x &&
                            mousePos.y >= canvasPos.y && mousePos.y <= canvasPos.y + canvasSize.y)
                        {
                            const sf::Vector2f bufferPos = {
                                ((mousePos.x - canvasPos.x) / canvasSize.x) * 800,
                                ((mousePos.y - canvasPos.y) / canvasSize.y) * 600
                            };

                            if (bufferPos.x < 800 && bufferPos.y < 600) {
                                drawingEngine.Draw(bufferPos);
                            }
                        }
                    }
                    break;
                    case sf::Event::Resized:
                        // Enforce minimum size
                        unsigned newWidth = std::max(event.size.width, MIN_WINDOW_WIDTH);
                        unsigned newHeight = std::max(event.size.height, MIN_WINDOW_HEIGHT);

                        // Update window size if needed
                        if (newWidth != event.size.width || newHeight != event.size.height) {
                            window.setSize({ newWidth, newHeight });
                        }

                        // Update layout with final dimensions
                        updateLayout(newWidth, newHeight);
                        break;
                        break;

            }
        }

        // Clear screen
        canvas->clear(tgui::Color::White);

        canvas->draw(drawingEngine.GetMainSprite());
        canvas->display();

        window.clear();
        gui.draw();
        window.display();

    }

    return 0;
}