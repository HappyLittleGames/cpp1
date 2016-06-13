#pragma once
#include <iostream>
#include "CommandLog.h"
#include "EntityHandler.h"
#include "MenuWindow.h"
#include <windows.h>



int main()
{
	bool m_debugMode = false;

	sf::Vector2i mousePos;
	sf::Clock clock;
	sf::Time time;
	float deltaTime = 0;

	EntityHandler* entityHandler = EntityHandler::GetInstance();
	CommandLog* commandLog = CommandLog::GetInstance();

// window setup
	sf::VideoMode windowMode = sf::VideoMode(256, 512);
	sf::RectangleShape whiteShape;

	sf::RenderWindow window(windowMode, "whitespace", sf::Style::None);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	whiteShape.setSize(sf::Vector2f(256.0f, 512.0f));
	whiteShape.setFillColor(sf::Color::White);
	entityHandler->MakeHeader(window.getSize().x);


// initialize player
	entityHandler->SpawnPlayer(window.getSize());
	entityHandler->GetPlayer()->SetLives(0);

// initial invader(s)
	//entityHandler->MakeInvaders(window.getSize().x, 1, "invader();");


	if (!m_debugMode)
	{
		FreeConsole();
		// debug grid setup
		entityHandler->MakeLines(window.getSize(), 8);
	}
	else
	{
		AllocConsole();
	}


// sfml event loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case(sf::Event::MouseMoved) :
				if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && (sf::Mouse::getPosition(window).y <= 30)) // this in handler I guess..
				{
					window.setPosition(window.getPosition() + sf::Vector2i(event.mouseMove.x, event.mouseMove.y) - mousePos);
				}
				else
				{
					mousePos = sf::Mouse::getPosition(window);
				}
				break;

			case(sf::Event::Closed):
				window.close();
				break;
				
			case(sf::Event::KeyPressed):
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					commandLog->AddEntry(entityHandler->GetPlayer()->GetCommand()->getString());
					MenuWindow::RunCommand(entityHandler->GetPlayer()->GetCommand()->getString(), window);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					commandLog->CycleDown();
					sf::String str = commandLog->GetEntry();
					entityHandler->GetPlayer()->EnterString(str);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					commandLog->CycleUp();
					sf::String str = commandLog->GetEntry();
					entityHandler->GetPlayer()->EnterString(str);
				}
			}
				
			case(sf::Event::TextEntered):
			{
				if (entityHandler->GetPlayer()->EnterText(event))
				{
					//MenuWindow::RunCommand(entityHandler->GetPlayer()->GetCommand()->getString(), window);
					//entityHandler->MakeLazer(entityHandler->GetPlayer()->GetCommand());
					m_debugMode = !m_debugMode;
					if (!m_debugMode)
					{
						FreeConsole();				
					}
					else
					{
						entityHandler->MakeLines(window.getSize(), 8);
						AllocConsole();
					}
				}
				break;
			}
			}
		}
// sfml event loop end


// updating and drawing 

		window.clear();

		time = clock.getElapsedTime();
		//std::cout << "Delta Time: " << time.asSeconds() << "." << std::endl;
		deltaTime = time.asSeconds();
		clock.restart();

		// UPDATE THE THINGS
		entityHandler->UpdateSpawns(window, deltaTime);
		
		entityHandler->UpdateEverything(window, deltaTime);

		//if (entityHandler->GetPlayer()->GetLives() > 0)
		//{
			// GRID
			if (m_debugMode)
			{
				for each (sf::RectangleShape* line in entityHandler->GetLines())
				{
					window.draw(*line);
				}
			}

			// COLLISIONS
			entityHandler->RunCollisions(entityHandler->GetInvaders(), entityHandler->GetLazers());

			// INVADERS
			for each (Invader* invader in entityHandler->GetInvaders())
			{
				//invader->MobileState(true);
				//invader->Update(window, deltaTime);

				if (m_debugMode)
				{
					window.draw(invader->GetBoundingBox().debugRect);
				}
				window.draw(*invader->GetText());
			}

			// LAZERS
			for each (LazerText* lazer in entityHandler->GetLazers())
			{
				if ((m_debugMode) && (entityHandler->GetLazers().size() > 0))
				{
					window.draw(lazer->GetBoundingBox().debugRect);
				}
				window.draw(*lazer->GetText());
			}

			// SPLOSIONS
			for each (TextObject* explosion in entityHandler->GetExplosions())
			{
				window.draw(*explosion->GetText());
			}

			// PLAYER
			{
				if (m_debugMode)
				{
					window.draw(entityHandler->GetPlayer()->GetBoundingBox().debugRect);
				}
				window.draw(*entityHandler->GetPlayer()->GetText());
				window.draw(*entityHandler->GetPlayer()->GetCommand());
			}
		//}
		window.draw(entityHandler->GetHeader());
		window.display();
	}

	return 0;
}
