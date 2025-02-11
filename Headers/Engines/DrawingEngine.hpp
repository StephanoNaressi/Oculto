#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Oculto {
	class DrawingEngine {
		public:
			DrawingEngine() noexcept;
			void SetScale(float scale) { _mainSprite.setScale(scale, scale); }
			sf::Sprite& GetMainSprite() noexcept;
			void Draw(sf::Vector2f mouseCoords) noexcept;
		private:
			sf::Image _mainBuffer;
			sf::Texture _mainTexture;
			sf::Sprite _mainSprite;
			bool _needsUpdate = false;
		//Mouse Coords
			sf::Vector2f _mousePosition;
	};
}