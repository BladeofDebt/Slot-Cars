#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Bullet.h"

Bullet::Bullet(Map* _map, EntityTeam _team)
	: Entity(_map, EntityID::Bullet, _team)
{
}

Bullet::~Bullet()
{
}
