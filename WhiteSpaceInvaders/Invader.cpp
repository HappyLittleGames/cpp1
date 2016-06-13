#include "Invader.h"



Invader::Invader()
{
}


Invader::~Invader()
{
}


void Invader::Update(sf::RenderWindow& window, float deltaTime)
{
	FollowWindow(window);
	m_text->setPosition(m_text->getPosition() + m_speed * deltaTime);
}


void Invader::Move(sf::Event event)
{
	if (event.key.code == sf::Keyboard::D)
	{
		m_text->setPosition(m_text->getPosition() - sf::Vector2f(-5, 0));
	}
	if (event.key.code == sf::Keyboard::A)
	{
		m_text->setPosition(m_text->getPosition() - sf::Vector2f(5, 0));
	}
	if (event.key.code == sf::Keyboard::W)
	{
		m_text->setPosition(m_text->getPosition() - sf::Vector2f(0, 5));
	}
	if (event.key.code == sf::Keyboard::S)
	{
		m_text->setPosition(m_text->getPosition() - sf::Vector2f(0, -5));
	}
}
