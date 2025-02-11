#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "DrawingEngine.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 1400, 600 }), "Oculto");
    tgui::Gui gui{ window };

    Oculto::DrawingEngine drawingEngine;
    //Color Picker
    auto colorPicker = tgui::ColorPicker::create("Choose a colour!", tgui::Color::Black);
    gui.add(colorPicker);
    colorPicker->setPosition(0, 0);
    colorPicker->setSize(tgui::bindWidth(gui) * 0.45f, tgui::bindHeight(gui));

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
    
    //Variables
    float cwR = 1;
    float chR = 1;
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
                            
                            sf::Vector2i localPosition = { sf::Mouse::getPosition(window).x - static_cast<int>(canvas->getPosition().x / (1400.f / window.getSize().x)),
                                sf::Mouse::getPosition(window).y - static_cast<int>(canvas->getPosition().y) };

                            if (localPosition.x >= 0 && localPosition.x < canvas->getSize().x / (1400.f / window.getSize().x) &&
                                localPosition.y >= 0 && localPosition.y < canvas->getSize().y / (600.f / window.getSize().y)) {
                                // get the current mouse position in the window
                                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                                // convert it to world coordinates
                                sf::Vector2f worldPos = window.mapPixelToCoords(localPosition);
                                drawingEngine.Draw(worldPos);
                            }
                        }
                    break;
                    case sf::Event::Resized:
                        // Window
                        float screenW = 1400.f;
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

                        //Canvas
                        float canvasW = 800.f;
                        float canvasH = 600.f;

                        tgui::Vector2f canvasSize = canvas->getSize();

                        chR = canvasH / canvasW;
                        cwR = canvasW / canvasH;

                        if (canvasSize.y * cwR <= canvasSize.x) {
                            canvasSize.x = canvasSize.y * cwR;
                        }
                        else if (canvasSize.x * chR <= canvasSize.y) {
                            canvasSize.y = canvasSize.x * chR;
                        }

                        canvas->setSize(canvasSize);
                        break;

            }
        }

        // Clear screen
        canvas->clear(tgui::Color::White);
        window.clear();

        // Draw here

        //Draw your buffer
        //window.draw(drawingEngine.GetMainSprite());
        canvas->draw(drawingEngine.GetMainSprite());
        gui.draw();
        // Update the window
        canvas->display();
        window.display();

    }

    return 0;
}