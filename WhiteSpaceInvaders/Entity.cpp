#include "Entity.h"



Entity::Entity()
{
	m_exploding = false;
}


Entity::~Entity()
{
}


void Entity::FollowingWindowState(bool state)
{
	m_followingWindow = state;
}

void Entity::SetSpeed(sf::Vector2f speed)
{
	m_speed = speed;
}

void Entity::SetExploding(bool status)
{
	m_exploding = status;
}

bool Entity::GetExploding()
{
	return m_exploding;
}


