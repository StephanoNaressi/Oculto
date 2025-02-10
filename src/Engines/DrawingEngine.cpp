#include "DrawingEngine.hpp"

namespace Oculto {
	DrawingEngine::DrawingEngine() noexcept
		: _mainBuffer(std::make_shared<sf::Image>(sf::Vector2u(800, 600), sf::Color(255, 255, 255))),
		_mainTexture(std::make_shared<sf::Texture>(*(_mainBuffer.get()))),
		_mainSprite(std::make_shared<sf::Sprite>(*(_mainTexture.get())))
	{

	}

	std::shared_ptr <sf::Sprite> DrawingEngine::GetMainSprite() noexcept {
		return _mainSprite;
	}

	void DrawingEngine::Draw(sf::Vector2f mouseCoords) noexcept{
		sf::Vector2u mouseVector(mouseCoords.x, mouseCoords.y);
		_mainBuffer->setPixel(mouseVector, sf::Color(0,0,0));
		_mainTexture = std::make_shared<sf::Texture>(*(_mainBuffer.get()));
		_mainSprite = std::make_shared<sf::Sprite>(*(_mainTexture.get()));
	}

	void DrawingEngine::ResizeBuffer(sf::Vector2u windowSize) noexcept{
		_mainBuffer->resize(windowSize);
		_mainTexture = std::make_shared<sf::Texture>(*(_mainBuffer.get()));
		_mainSprite = std::make_shared<sf::Sprite>(*(_mainTexture.get()));
	}
}