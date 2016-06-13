#pragma once
#include "WindowType.h"

static class MenuWindow : public WindowType
{
public:
	MenuWindow();
	~MenuWindow();

	void UpdateAll(sf::RenderWindow& window, float deltaTime);

	void WindowTemplate(sf::RenderWindow& window);

	static void RunCommand(std::string, sf::RenderWindow& window);

	static std::vector<std::string> GetCommands();
};

