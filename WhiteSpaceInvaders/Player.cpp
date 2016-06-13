#include "Player.h"



Player::Player()
{
	m_lives = 1;
}


Player::~Player()
{
}


void Player::Update(sf::RenderWindow& window, float deltaTime)
{

}


void Player::Move(sf::Event event)
{
	if (event.key.code == sf::Keyboard::D)
	{
		m_text->setPosition(m_text->getPosition() - sf::Vector2f(-5, 0));
		//m_command->GetText()->setPosition(m_command->GetText()->getPosition() - sf::Vector2f(-5, 0));
	}
	if (event.key.code == sf::Keyboard::A)
	{
		m_text->setPosition(m_text->getPosition() - sf::Vector2f(5, 0));
		//m_command->GetText()->setPosition(m_command->GetText()->getPosition() - sf::Vector2f(5, 0));
	}
	if (event.key.code == sf::Keyboard::W)
	{
		m_text->setPosition(m_text->getPosition() - sf::Vector2f(0, 5));
		//m_command->GetText()->setPosition(m_command->GetText()->getPosition() - -sf::Vector2f(0, 5));
	}
	if (event.key.code == sf::Keyboard::S)
	{
		m_text->setPosition(m_text->getPosition() - sf::Vector2f(0, -5));
		//m_command->GetText()->setPosition(m_command->GetText()->getPosition() - sf::Vector2f(0, -5));
	}
}
