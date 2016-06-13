#pragma once
#include "TextObject.h"

class Player : public TextObject
{
public:
	Player();
	~Player();

	void Update(sf::RenderWindow&, float) override;
	void Move(sf::Event event) override;
};

