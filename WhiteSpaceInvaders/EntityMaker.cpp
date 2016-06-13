#include "EntityMaker.h"

//factory

EntityMaker::EntityMaker()
{
}


EntityMaker::~EntityMaker()
{
}


TextObject* EntityMaker::MakeEntity(std::string entityType)
{
	// try to template this?
	TextObject* entity = nullptr;

	if (entityType == "Player")
	{
		entity = new Player();

		entity->SetText(new sf::Text());
		entity->GetText()->setCharacterSize(18);
		entity->GetText()->setStyle(sf::Style::None);
		entity->GetText()->setString("C/:> ");
		entity->GetText()->setColor(sf::Color::White);
		entity->GetText()->rotate(-90);
		entity->SetLives(1);
		//entity->MobileState(false);

		entity->SetCommand(new sf::Text());
		entity->GetCommand()->setCharacterSize(18);
		entity->GetCommand()->setStyle(sf::Style::None);
		entity->GetCommand()->setString("ww");
		entity->GetCommand()->setColor(sf::Color::White);
		entity->GetCommand()->rotate(-90);

		// font and position handled in handler for now
	}
	else if (entityType == "Invader")
	{
		entity = new Invader();
		entity->SetSpeed(sf::Vector2f(0.0f, 30.0f));

		entity->SetText(new sf::Text());
		entity->GetText()->setCharacterSize(16);
		entity->GetText()->setStyle(sf::Style::None);
		entity->GetText()->setString("Invader(); ");
		entity->GetText()->setColor(sf::Color::White);
		entity->GetText()->rotate(90);
		//entity->MobileState(true);

		entity->SetCommand(new sf::Text());
		entity->GetCommand()->setCharacterSize(16);
		entity->GetCommand()->setStyle(sf::Style::None);
		entity->GetCommand()->setString("");
		entity->GetCommand()->setColor(sf::Color::White);
		entity->GetCommand()->rotate(90);

		// font and position handled in EntityHandler, not great
	}
	else if (entityType == "Invader")
	{
		entity = new TextObject();
		entity->SetSpeed(sf::Vector2f(0,0));

		entity->SetText(new sf::Text());
		entity->GetText()->setCharacterSize(16);
		entity->GetText()->setStyle(sf::Style::None);
		entity->GetText()->setString("FORMATSTR			description");
		entity->GetText()->setColor(sf::Color::White);
		entity->GetText()->rotate(-90);
		//entity->MobileState(true);

		// font and position handled in EntityHandler, not great
	}
	else if (entityType == "Explosion")
	{
		
		entity = new Explosion();
		entity->SetSpeed(sf::Vector2f(0, 0));
		entity->SetText(new sf::Text());
		entity->GetText()->setCharacterSize(16);
		entity->GetText()->setStyle(sf::Style::None);
		entity->GetText()->setColor(sf::Color::Yellow);
		entity->GetText()->rotate(90);

		switch (std::rand() % 4)
		{
		case (0) :
		{
			entity->GetText()->setString("kaboom!();");
		}
		case (1) :
		{
			entity->GetText()->setString("blam!!!();");
		}
		case (2) :
		{
			entity->GetText()->setString("pow!!!!();");
		}
		case (3) :
		{
			entity->GetText()->setString("booom!!();");
		}
		}

	}
	return entity;
}