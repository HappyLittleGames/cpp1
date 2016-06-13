#include "MenuWindow.h"



MenuWindow::MenuWindow()
{
}


MenuWindow::~MenuWindow()
{
}


void MenuWindow::UpdateAll(sf::RenderWindow& window, float deltaTime)
{

}


void MenuWindow::WindowTemplate(sf::RenderWindow& window)
{
	sf::VideoMode windowMode = sf::VideoMode(256, 512);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
}


std::vector<std::string> MenuWindow::GetCommands()
{
	std::vector<std::string> commands;

	//commands.push_back("COMMAND			description");
	commands.push_back("newgame             start a new game");
	commands.push_back("lazer               pew pew pew pew");
	commands.push_back("reset               resets position, will be helpful");
	commands.push_back("options             there are no options");
	commands.push_back("credits             as if any");
	commands.push_back("quit                give up and quit");

	return commands;
}


void MenuWindow::RunCommand(std::string string, sf::RenderWindow& window)
{
	EntityHandler* entityHandler = EntityHandler::GetInstance();
	if (string == "help")
	{
		int index = 0;
		for each (std::string cString in GetCommands())
		{
			index++;
			entityHandler->MakeLazer(entityHandler->GetPlayer()->GetCommand());
			entityHandler->GetLazers().back()->GetText()->setString(cString);
			entityHandler->GetLazers().back()->SetSpeed(sf::Vector2f(15,0));
			entityHandler->GetLazers().back()->GetText()->setPosition(entityHandler->GetLazers().back()->GetText()->getPosition() + sf::Vector2f(entityHandler->GetLazers().back()->GetText()->getCharacterSize() * index, 0));

		}
	}
	else if (string == "lazer")
	{
		entityHandler->MakeLazer(entityHandler->GetPlayer()->GetCommand());
	}
	else if (string == "newgame")
	{
		entityHandler->ClearLazers();
		entityHandler->MakeInvaders(256, 1, "Invader();");
		entityHandler->GetPlayer()->SetLives(1);
	}
	else if (string == "quit")
	{
		window.close();
	}
	else
	{
		entityHandler->MakeLazer(entityHandler->GetPlayer()->GetCommand());
		entityHandler->GetLazers().back()->GetText()->setString("'" + string + "' is not recognized as an internal nor external command, \noperable program or batch file.");
		entityHandler->GetLazers().back()->SetSpeed(sf::Vector2f(15, 0));
	}
	entityHandler->GetPlayer()->GetCommand()->setString("");
}