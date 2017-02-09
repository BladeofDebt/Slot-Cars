#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet(Level* _level, EntityTeam _team)
	: Entity(_level, EntityID::Bullet, _team)
{
	switch (_team)
	{
	case EntityTeam::Player1:
		m_color = CToIColor(255, 255, 0, 0);
		break;
	case EntityTeam::Player2:
		m_color = CToIColor(255, 0, 0, 255);
		break;
	default:
		break;
	}
	m_texture = TextureManager::GetSingleton()->Get("bullet.png");
	m_speed = 5;
	m_lifeTime = 0;
	m_lifeTimeMax = 4;
}

Bullet::~Bullet()
{
}

void Bullet::Update(float a_deltatime)
{
	Entity::Update(a_deltatime);
	if (!m_activeGet) { return; }

	//Speed Control
	if (m_lifeTime > 0)
		m_lifeTime -= a_deltatime;
	if (m_lifeTime <= 0)
	{
		m_activeSet = false;
		m_lifeTime = m_lifeTimeMax;
	}
}

void Bullet::OnCollision(Entity * a_entity)
{
	if (!m_activeGet) { return; }
	switch (a_entity->m_id)
	{
	case EntityID::Player:
		m_activeSet = false;
		break;
	case EntityID::Bullet:
		m_activeSet = false;
		break;
	default:
		break;
	}
}
