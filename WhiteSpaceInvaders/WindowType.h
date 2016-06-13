#pragma once
#include "SFML\Graphics.hpp"
#include "EntityHandler.h"

class WindowType
{
public:
	WindowType();
	~WindowType();
	void UpdateAll(sf::RenderWindow& window, float deltaSeconds);
protected:
	sf::VideoMode m_windowMode = sf::VideoMode(256, 512);
};

