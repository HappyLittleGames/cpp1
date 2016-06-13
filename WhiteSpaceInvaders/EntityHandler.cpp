#include "EntityHandler.h"

//facade

EntityMaker entityMaker;
EntityHandler* EntityHandler::m_instance = nullptr;

EntityHandler::EntityHandler()
{
	if (!m_font.loadFromFile("lucon.ttf"))
	{
		std::cout << "Failed to load font 'lucon.tff'" << std::endl;
	}
}


EntityHandler* EntityHandler::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new EntityHandler();
		m_instance->m_elapsedTime = 0;
		m_instance->m_spawnCooldown = 2;
		m_instance->m_cooldownProgress = 0;
	}
	return m_instance;
}


void EntityHandler::SpawnPlayer(sf::Vector2u windowSize)
{
	m_player = entityMaker.MakeEntity("Player");

	m_player->GetText()->setPosition(sf::Vector2f((windowSize.x / 2), windowSize.y - 24));
	m_player->GetText()->setFont(m_font);

	m_player->GetCommand()->setPosition(sf::Vector2f((windowSize.x / 2), windowSize.y - (74)));
	m_player->GetCommand()->setFont(m_font);
}


TextObject* EntityHandler::GetPlayer()
{
	return m_player;
}


void EntityHandler::MakeInvaders(int windowSize, int amount, sf::String text)
{

	for (int i = 0; i < amount; i++)
	{
		m_invaders.push_back(entityMaker.MakeEntity("Invader"));

		m_invaders.back()->GetText()->setPosition(((windowSize/amount) * i) + 28.0f, (10.0f + EntityHandler::GetInstance()->GetHeader().getSize().y));
		m_invaders.back()->GetText()->setFont(m_font);
	}
}


std::vector<TextObject*> EntityHandler::GetInvaders()
{
	return m_invaders;
}


void EntityHandler::MovePlayer(sf::Event event)
{
	if (event.key.code == sf::Keyboard::D)
	{
		m_player->GetText()->setPosition(m_player->GetText()->getPosition() - sf::Vector2f(-5, 0));
	}
	if (event.key.code == sf::Keyboard::A)
	{
		m_player->GetText()->setPosition(m_player->GetText()->getPosition() - sf::Vector2f(5, 0));
	}
	if (event.key.code == sf::Keyboard::W)
	{
		m_player->GetText()->setPosition(m_player->GetText()->getPosition() - sf::Vector2f(0, 5));
	}
	if (event.key.code == sf::Keyboard::S)
	{
		m_player->GetText()->setPosition(m_player->GetText()->getPosition() - sf::Vector2f(0, -5));
	}
}


void EntityHandler::MakeLines(sf::Vector2u windowSize, int amount)
{
	for (int i = 0; i < amount*8; i++)
	{
		m_lines.push_back(new sf::RectangleShape());
		m_lines.back()->setFillColor(sf::Color::Blue);
		m_lines.back()->setSize(sf::Vector2f(2, windowSize.y));
		m_lines.back()->setPosition(sf::Vector2f((windowSize.x / amount * i), 0));
	}
	for (int i = 1; i < amount * 8; i++)
	{
		m_lines.push_back(new sf::RectangleShape());
		m_lines.back()->setFillColor(sf::Color::Blue);
		m_lines.back()->setSize(sf::Vector2f(2, windowSize.y));
		m_lines.back()->setPosition(sf::Vector2f(-(windowSize.x / amount * i), 0));
	}
	for (int i = 0; i < amount*2; i++)
	{
		m_lines.push_back(new sf::RectangleShape());
		m_lines.back()->setFillColor(sf::Color::Blue);
		m_lines.back()->setSize(sf::Vector2f(windowSize.y, 2));
		m_lines.back()->setPosition(sf::Vector2f(0,(windowSize.x / amount * i)));
	}
}


std::vector<sf::RectangleShape*> EntityHandler::GetLines()
{
	return m_lines;
}


void EntityHandler::MakeHeader(int windowWidth)
{
	m_header.setPosition(sf::Vector2f(0, 0));
	m_header.setSize(sf::Vector2f(windowWidth, 30));
	m_header.setFillColor(sf::Color::White);
}


sf::RectangleShape EntityHandler::GetHeader()
{
	return m_header;
}


void EntityHandler::MakeLazer(sf::Text* otherText)
{
	m_lazers.push_back(new LazerText());
	m_lazers.back()->SetText(new sf::Text());
	m_lazers.back()->GetText()->setCharacterSize(otherText->getCharacterSize());
	m_lazers.back()->GetText()->setStyle(otherText->getStyle());
	m_lazers.back()->GetText()->setString("pew();");
	m_lazers.back()->GetText()->setColor(otherText->getColor());
	m_lazers.back()->GetText()->rotate(otherText->getRotation());

	m_lazers.back()->GetText()->setFont(m_font);
	m_lazers.back()->GetText()->setPosition(otherText->getPosition());
	m_lazers.back()->SetSpeed(sf::Vector2f(0,-250));
}


std::vector<LazerText*>& EntityHandler::GetLazers()
{
	return m_lazers;
}


void EntityHandler::ClearLazers()
{
	m_lazers.clear();
}


std::vector<TextObject*> EntityHandler::GetExplosions()
{
	return m_explosions;
}

bool EntityHandler::EnterCommand(sf::Text* text)
{
	std::cout << "Command Entered; " << (std::string)text->getString() << std::endl;

	if (text->getString() == "pew();")
	{
		//MakeLazer(text);
		return true;
	}
	else
	{
		return false;
	}
}


void EntityHandler::UpdateSpawns(sf::RenderWindow& window, float deltaTime)
{
	m_elapsedTime += deltaTime;
	if (m_elapsedTime > m_spawnCooldown)
	{
		m_invaders.push_back(entityMaker.MakeEntity("Invader"));
		m_invaders.back()->GetText()->setFont(m_font);

		sf::Vector2i systemPos = sf::Vector2i(0, 0) - window.getPosition();
		float xPos = (std::rand() % (sf::VideoMode::getDesktopMode().width - 32) + 32);

		m_invaders.back()->GetText()->setPosition(xPos, systemPos.y);

		m_elapsedTime = 0;

		m_spawnCooldown -= deltaTime / 3;
		if (m_spawnCooldown < 0.1f)
		{
			m_spawnCooldown = 0.1f;
		}
	}

}


void EntityHandler::RunCollisions(std::vector<TextObject*> &targets, std::vector<LazerText*> &munitions)
{
	std::vector<TextObject*> exploders;

	for each (TextObject* target in targets)
	{
		bool collision = false;

		for each (TextObject* munition in munitions)
		{
			if (munition->GetText()->getString() == "pew();")
			{
				if (CheckCollision(munition->GetBoundingBox(), target->GetBoundingBox()))
				{
					std::cout << "Collision Detected" << std::endl;
					collision = true;
					m_explosions.push_back(entityMaker.MakeEntity("Explosion"));
					m_explosions.back()->GetText()->setPosition(target->GetText()->getPosition());
					m_explosions.back()->GetText()->setFont(*target->GetText()->getFont());

					munition->SetExploding(true);
				}
			}
		}

		if (collision)
		{
			//target->GetText()->setString("kabooom();");
			target->SetExploding(true);
		}
		else
		{
			target->SetExploding(false);
		}
	}
	
	if (targets.size() > 0)
	{
		for (int i = targets.size() - 1; i >= 0; i--)
		{
			if (targets[i]->GetExploding())
			{
				targets.erase(targets.begin() + i);
				std::cout << "-----" << targets.size() << std::endl;
			}
		}
	}

	if (munitions.size() > 0)
	{
		for (int i = munitions.size() - 1; i >= 0; i--)
		{
			if (munitions[i]->GetExploding())
			{
				munitions.erase(munitions.begin() + i);
				std::cout << "-----" << munitions.size() << std::endl;
			}
		}
	}

	/*m_invaders = targets;
	m_lazers = munitions;*/
}


bool EntityHandler::CheckCollision(BoundingBox entity1, BoundingBox entity2)
{
	if ((entity1.topRight.x < entity2.topLeft.x) || (entity1.topLeft.x > entity2.topRight.x))
	{
		return false;
	}
	if ((entity1.botRight.y < entity2.topLeft.y) || (entity1.topLeft.y > entity2.botRight.y))
	{
		return false;
	}
	std::cout << "Collision!" << std::endl;
	return true;
}


void EntityHandler::UpdateEverything(sf::RenderWindow & window, float deltaTime)
{
	// INVADERS
	for each (Invader* invader in m_invaders)
	{
		//invader->MobileState(true);
		invader->Update(window, deltaTime);
		if ((invader->GetText()->getPosition().y + window.getPosition().y) > sf::VideoMode::getDesktopMode().height)
		{
			m_player->SetLives(0);
		}
	}
	// LAZERS
	for each (LazerText* lazer in m_lazers)
	{
		//lazer->MobileState(true);
		lazer->Update(window, deltaTime);
	}
	// SPLOSIONS
	bool anythingExploding = false;
	for each (TextObject* explosion in m_explosions)
	{
		//invader->MobileState(true);
		explosion->Update(window, deltaTime);
		if (explosion->GetText()->getScale().x > 0.1)
		{
			anythingExploding = true;
		}
	}
	if (!anythingExploding)
	{
		m_explosions.clear();
	}

		// COLLISIONS
	RunCollisions(m_invaders, m_lazers);
	// GUY
	m_player->Update(window, deltaTime);

}