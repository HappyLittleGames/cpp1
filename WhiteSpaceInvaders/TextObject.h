#pragma once
#include"Entity.h"

struct BoundingBox
{
	BoundingBox() {};
	sf::Vector2f topLeft, topRight, botLeft, botRight;
	sf::RectangleShape debugRect;
};

class TextObject : public Entity
{

public:

	sf::Text* GetText();
	void SetText(sf::Text* text);

	sf::Text* GetCommand();
	void SetCommand(sf::Text* text);

	bool EnterText(sf::Event event);
	void EnterString(sf::String);

	void Update(sf::RenderWindow&, float) override;
	void Move(sf::Event event) override;

	const BoundingBox GetBoundingBox();

	const int GetLives();
	void SetLives(int amount);

protected:
	sf::Text* m_text;
	sf::Text* m_command;

	BoundingBox m_boundingBox;

	sf::Vector2f m_oldWindowPos;
	void FollowWindow(sf::RenderWindow&);

	int m_lives;

private:

	virtual void Move(sf::Vector2f value);
};

