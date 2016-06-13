#pragma once
#include "TextObject.h"

class Explosion : public TextObject
{
public:
	Explosion();
	~Explosion();

	void Update(sf::RenderWindow&, float deltaTime) override;
private:
	bool m_shockwaving;
	float m_explosionSpeed;
};