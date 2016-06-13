#pragma once
#include "TextObject.h"
class LazerText : public TextObject
{
public:
	LazerText();
	//LazerText(sf::Text*);
	~LazerText();

	void Update(sf::RenderWindow&, float) override;
private:
};

