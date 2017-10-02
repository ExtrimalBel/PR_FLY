#pragma once
#include <SFML/Graphics.hpp>

// Return the a float rect as an int rect.
bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b,
	const sf::Image& imgA, const sf::Image& imgB);
inline sf::IntRect FToIRect(const sf::FloatRect& f);