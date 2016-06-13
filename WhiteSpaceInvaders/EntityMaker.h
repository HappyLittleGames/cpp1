#pragma once
#include "Invader.h"
#include "Player.h"
#include "LazerText.h"
#include "Explosion.h"

static class EntityMaker
{

	//factory

public:
	EntityMaker();
	~EntityMaker();

	TextObject* MakeEntity(std::string entityType);
};

