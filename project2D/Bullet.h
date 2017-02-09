#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Level* _level, EntityTeam _team);
	~Bullet();

	void Update(float a_deltatime) override;
	void OnCollision(Entity* a_entity) override;

	float m_lifeTime, m_lifeTimeMax;
private:

};
