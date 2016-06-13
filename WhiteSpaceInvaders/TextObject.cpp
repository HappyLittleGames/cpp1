#include "TextObject.h"



void TextObject::Move(sf::Vector2f value)
{
	m_text->setPosition(value);
}


const int TextObject::GetLives()
{
	return m_lives;
}

void TextObject::SetLives(int amount)
{
	m_lives = amount;
}


sf::Text* TextObject::GetText()
{
	return this->m_text;
}


void TextObject::SetText(sf::Text* text)
{
	m_text = text;
}


sf::Text* TextObject::GetCommand()
{
	return this->m_command;
}


void TextObject::SetCommand(sf::Text* text)
{
	m_command = text;
}


bool TextObject::EnterText(sf::Event event)
{
	std::cout << "input " << event.key.code << std::endl;
	if (event.key.code == sf::Keyboard::Return)
	{
		return false;
	}
	else if (event.key.code == sf::Keyboard::F1)
	{
		return true;
	}
	else if (event.key.code == sf::Keyboard::BackSpace)
	{
		std::string tempString = m_command->getString();
		if (tempString.size() > 0)
		{
			tempString.erase(tempString.end() - 1);
			m_command->setString(tempString);
		}
		return false;
	}
	else if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down))
	{
		std::cout << "Memento();" << std::endl;
		return false;
	}
	else if (((event.text.unicode >= 65) && (event.text.unicode <= 240)) || event.text.unicode == 59 || event.text.unicode == 40 || event.text.unicode == 41)
	{
		char myChar = event.key.code;
		m_command->setString(m_command->getString() + myChar);
		return false;
	}
	else
	{
		return false;
	}
}

void TextObject::EnterString(sf::String string)
{
	m_command->setString(string);
}


void TextObject::Update(sf::RenderWindow& window, float deltaTime)
{

}


void TextObject::Move(sf::Event event)
{

}

const BoundingBox TextObject::GetBoundingBox()
{
	if (m_text->getRotation() == 90)
	{
		m_boundingBox.topLeft = m_text->getPosition() +		sf::Vector2f(m_text->getCharacterSize(), 0);
		m_boundingBox.topRight = m_text->getPosition();		
		m_boundingBox.botLeft = m_text->getPosition() +		sf::Vector2f(m_text->getCharacterSize(), (m_text->getCharacterSize() * 0.5) * (m_text->getString().getSize()));
		m_boundingBox.botRight = m_text->getPosition() +	sf::Vector2f(0, (m_text->getCharacterSize() * 0.5) * m_text->getString().getSize());
	}
	else if (m_text->getRotation() == -90)
	{
		m_boundingBox.topLeft = m_text->getPosition() +		sf::Vector2f(0, (m_text->getCharacterSize() * 0.5) * m_text->getString().getSize());
		m_boundingBox.topRight = m_text->getPosition() +	sf::Vector2f(m_text->getCharacterSize(), (m_text->getCharacterSize() * 0.5) * (m_text->getString().getSize()));
		m_boundingBox.botLeft = m_text->getPosition();		
		m_boundingBox.botRight = m_text->getPosition() +	sf::Vector2f(m_text->getCharacterSize(), 0);
	}
	else
	{
		m_boundingBox.topLeft = m_text->getPosition() + sf::Vector2f(0, (m_text->getCharacterSize() * 0.5) * m_text->getString().getSize());
		m_boundingBox.topRight = m_text->getPosition() + sf::Vector2f(m_text->getCharacterSize(), (m_text->getCharacterSize() * 0.5) * (m_text->getString().getSize()));
		m_boundingBox.botLeft = m_text->getPosition();
		m_boundingBox.botRight = m_text->getPosition() + sf::Vector2f(m_text->getCharacterSize(), 0);
	}
	

	m_boundingBox.debugRect = sf::RectangleShape();
	m_boundingBox.debugRect.setPosition(m_text->getPosition());
	//m_boundingBox.debugRect.setRotation(m_text->getRotation());
	m_boundingBox.debugRect.setSize(m_boundingBox.botRight - m_boundingBox.topLeft);
	m_boundingBox.debugRect.setFillColor(sf::Color::Red);

	return m_boundingBox;
}


void TextObject::FollowWindow(sf::RenderWindow& window)
{
	sf::Vector2f windowPos = sf::Vector2f(window.getPosition().x, window.getPosition().y);
	if (!m_followingWindow)
	{
		sf::Vector2f posDif = m_oldWindowPos - windowPos;

		m_text->setPosition(m_text->getPosition() + posDif);

		m_oldWindowPos = windowPos;
	}
	else
	{
		m_oldWindowPos = windowPos;
		m_followingWindow = false;
	}
}

