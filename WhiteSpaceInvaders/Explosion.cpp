#include "Explosion.h"



Explosion::Explosion()
{
	m_explosionSpeed = std::rand() % 14 + 7;
}


Explosion::~Explosion()
{
}


void Explosion::Update(sf::RenderWindow& window, float deltaTime)
{
	FollowWindow(window);
	if (m_shockwaving)
	{
		m_text->setPosition(m_text->getPosition() + sf::Vector2f(m_explosionSpeed * deltaTime * 20, -m_explosionSpeed * deltaTime * 10));
		m_text->setScale(sf::Vector2f(m_text->getScale().x * (1 + (m_explosionSpeed/2 * deltaTime)), m_text->getScale().x * (1 + (m_explosionSpeed * 4 * deltaTime))));
		if (m_text->getScale().x > 2.0f)
		{
			m_shockwaving = false;
			m_text->setColor(sf::Color::Red);
		}
	}
	else
	{
		m_text->setPosition(m_text->getPosition() + sf::Vector2f(- m_explosionSpeed * deltaTime * 20, m_explosionSpeed * deltaTime * 10));
		m_text->setScale(sf::Vector2f(m_text->getScale().x * (1 - ((m_explosionSpeed * 2) * deltaTime)), m_text->getScale().x * (1 - ((m_explosionSpeed * .75) * deltaTime))));;
	}
}