#pragma once
#include <iostream>
#include "EntityMaker.h"
#include <algorithm>

//facade

class EntityHandler
{
public:
	static EntityHandler* GetInstance();

	void SpawnPlayer(sf::Vector2u windowSize);
	TextObject* GetPlayer();

	void MakeInvaders(int windowSize, int amount, sf::String text);
	std::vector<TextObject*> GetInvaders();
	void MovePlayer(sf::Event event);

	void MakeLines(sf::Vector2u windowSize, int amount);
	std::vector<sf::RectangleShape*> GetLines();

	void MakeHeader(int);
	sf::RectangleShape GetHeader();

	void MakeLazer(sf::Text*);
	std::vector<LazerText*>& GetLazers();
	void ClearLazers();

	std::vector<TextObject*> GetExplosions();

	bool EnterCommand(sf::Text*);

	void RunCollisions(std::vector<TextObject*> &targets, std::vector<LazerText*> &munitions);

	void UpdateSpawns(sf::RenderWindow& window, float deltaTime);

	void UpdateEverything(sf::RenderWindow &window, float deltaTime);
private:
	EntityHandler();

	static EntityHandler* m_instance;

	TextObject* m_player;

	std::vector<sf::RectangleShape*> m_lines;

	std::vector<TextObject*> m_invaders;

	std::vector<LazerText*> m_lazers;

	std::vector<TextObject*> m_explosions;

	sf::Font m_font;

	sf::RectangleShape m_header;

	bool CheckCollision(BoundingBox, BoundingBox);

	float m_spawnCooldown, m_cooldownProgress, m_elapsedTime;
};

