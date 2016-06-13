#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

class Entity
{
public:
	Entity();
	~Entity();

	virtual void Update(sf::RenderWindow& window, float deltaTime) = 0;
	virtual void Move(sf::Event event) = 0;

	void FollowingWindowState(bool);

	void SetSpeed(sf::Vector2f speed);

	void SetExploding(bool);
	bool GetExploding();
	
protected:
	bool m_followingWindow = true;
	sf::Vector2f m_speed;
	bool m_exploding;
private:

};

