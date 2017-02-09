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

	m_texture = TextureManager::GetSingleton()->Get("bullet.png");
}

Bullet::~Bullet()
{
}

void Bullet::Update(float a_deltatime)
{
	if (!m_active) { return; }
}

void Bullet::OnCollision(Entity * m_entity)
{
	if (!m_active) { return; }
}
