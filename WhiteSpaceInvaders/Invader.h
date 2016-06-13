#pragma once
#include "TextObject.h"

class Invader : public TextObject
{
public:
	Invader();
	~Invader();

	void Update(sf::RenderWindow&, float) override;
	void Move(sf::Event event) override;

private:
};

