#include "DrawingEngine.hpp"

namespace Oculto {
	DrawingEngine::DrawingEngine() noexcept
		: _mainBuffer(),
		_mainTexture(),
		_mainSprite()
	{
		_mainBuffer.create(800,600,sf::Color(255,255,255));
		_mainTexture.loadFromImage(_mainBuffer);
		_mainSprite.setTexture(_mainTexture, true);
	}

	sf::Sprite& DrawingEngine::GetMainSprite() noexcept {
		return _mainSprite;
	}

	void DrawingEngine::Draw(sf::Vector2f mouseCoords) noexcept{

		// Clamp coordinates to buffer dimensions
		const unsigned int x = static_cast<unsigned int>(std::round(mouseCoords.x));
		const unsigned int y = static_cast<unsigned int>(std::round(mouseCoords.y));
		// Clamp to buffer dimensions
		if (x < 800 && y < 600) {
			_mainBuffer.setPixel(x, y, sf::Color::Black);
			_mainTexture.update(_mainBuffer);
		}
	}

}