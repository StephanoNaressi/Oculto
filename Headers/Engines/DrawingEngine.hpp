#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Oculto {
	class DrawingEngine {
		public:
			DrawingEngine() noexcept;
			sf::Sprite& GetMainSprite() noexcept;
			void Draw(sf::Vector2f mouseCoords) noexcept;
		private:
			sf::Image _mainBuffer;
			sf::Texture _mainTexture;
			sf::Sprite _mainSprite;

		//Mouse Coords
			sf::Vector2f _mousePosition;
	};
}