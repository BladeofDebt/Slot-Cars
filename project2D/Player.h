#pragma once
#include "Entity.h"
#include <Input.h>

struct InputSet
{
	aie::EInputCodes accelerate, left, deccelerate, right, fire;
};

class Player : public Entity
{
public:
	Player();
	Player(InputSet _inputSet);
	~Player();

	void HandleInput();
	void Fire();

	InputSet m_inputSet;
};
