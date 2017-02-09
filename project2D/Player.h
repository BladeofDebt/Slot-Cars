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
	Player(Level* _level, EntityTeam _team, Bullet* a_bullet);
	~Player();
	
	void Update(float a_deltatime) override;
	void OnCollision(Entity* a_entity) override;
	void HandleInput(float a_deltatime);
	void Fire();

	InputSet m_inputSet;
	float m_lowSpeed, m_defaultSpeed, m_highSpeed, m_deathSpeed;
	float m_speedCooldown;
	float m_speedCooldownMax;
protected:
	const static InputSet PLAYER1_INPUTSET;
	const static InputSet PLAYER2_INPUTSET;

	Bullet* m_bullet;
};
