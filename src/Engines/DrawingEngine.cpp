#include "DrawingEngine.hpp"

namespace Oculto {
	DrawingEngine::DrawingEngine() noexcept
		: _mainBuffer(),
		_mainTexture(),
		_mainSprite()
	{
		_mainBuffer.create(800,600,sf::Color(255,255,255));
		_mainTexture.loadFromImage(_mainBuffer);
		_mainSprite.setTexture(_mainTexture);
	}

	sf::Sprite& DrawingEngine::GetMainSprite() noexcept {
		return _mainSprite;
	}

	void DrawingEngine::Draw(sf::Vector2f mouseCoords) noexcept{
		sf::Vector2u mouseVector(mouseCoords.x, mouseCoords.y);
		_mainBuffer.setPixel(mouseVector.x,mouseVector.y, sf::Color(0,0,0));
		_mainTexture.loadFromImage(_mainBuffer);
		_mainSprite.setTexture(_mainTexture);
	}

}