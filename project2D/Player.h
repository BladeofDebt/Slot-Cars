#pragma once
#include "Entity.h"
#include <Input.h>

namespace aie { class Texture; }
class Bullet;

struct InputSet
{
	aie::EInputCodes align, left, slowDown, right, fire, boost;
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
	void SetTurn(int _newTurn) override;

	InputSet m_inputSet;
	float m_lowSpeed, m_normalSpeed, m_highSpeed;
	float m_deathSpeed, m_deathSpeedMax;
	float m_speedCooldown;
	float m_speedCooldownMax;
	unsigned int m_slowColor;
	unsigned int m_normalColor;
	unsigned int m_boostColor;
	aie::Texture* m_textureForward, *m_textureLeft, *m_textureRight;

protected:
	const static InputSet PLAYER1_INPUTSET;
	const static InputSet PLAYER2_INPUTSET;

	Bullet* m_bullet;
};
