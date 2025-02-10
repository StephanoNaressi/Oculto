#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Oculto {
	class DrawingEngine {
		public:
			DrawingEngine() noexcept;
			std::shared_ptr <sf::Sprite> GetMainSprite() noexcept;
			void Draw(sf::Vector2f mouseCoords) noexcept;
			void ResizeBuffer(sf::Vector2u windowSize) noexcept;
		private:
			std::shared_ptr <sf::Image> _mainBuffer;
			std::shared_ptr <sf::Texture> _mainTexture;
			std::shared_ptr <sf::Sprite> _mainSprite;

		//Mouse Coords
			sf::Vector2f _mousePosition;
	};
}