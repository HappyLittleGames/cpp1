#include "LazerText.h"



LazerText::LazerText()
{
}


//LazerText::LazerText(sf::Text* other)
//{
//	sf::Text* textPtr = new sf::Text();
//	textPtr->setCharacterSize(other->getCharacterSize());
//	
//	textPtr->setCharacterSize(other->getCharacterSize());
//	textPtr->setStyle(other->getStyle());
//	textPtr->setString("(Lazer::Beam);");
//	textPtr->setColor(other->getColor());
//	textPtr->rotate(other->getRotation());
//	
//	m_text = textPtr;
//}


LazerText::~LazerText()
{
}


void LazerText::Update(sf::RenderWindow& window, float deltaTime)
{
	FollowWindow(window);
	m_text->setPosition(m_text->getPosition() + m_speed * deltaTime);
}
