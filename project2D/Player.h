#pragma once
#include "Entity.h"
#include <Input.h>

class Bullet;
struct InputSet
{
	aie::EInputCodes accelerate, left, deccelerate, right, fire;
};

class Player : public Entity
{
public:
	Player(Map* _map, EntityTeam _team, Bullet* a_bullet);
	~Player();
	
	void Update(float a_deltatime) override;
	void OnCollision(Entity* a_entity) override;
	void HandleInput();
	void Fire();

	InputSet m_inputSet;
protected:
	const static InputSet PLAYER1_INPUTSET;
	const static InputSet PLAYER2_INPUTSET;

	Bullet* m_bullet;
};
