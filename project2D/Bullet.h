#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Level* _level, EntityTeam _team);
	~Bullet();

	void Update(float a_deltatime) override;
	void OnCollision(Entity* m_entity) override;

private:

};
