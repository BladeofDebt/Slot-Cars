#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Entity.h"
#include <Texture.h>
#include <Renderer2D.h>
#include "TextureManager.h"

Entity::Entity(Map* _map, EntityID _id, EntityTeam _team)
	: m_map(_map), m_id(_id), m_team(_team)
{
}

Entity::~Entity()
{
}

void Entity::Draw(aie::Renderer2D * _renderer)
{
	_renderer->drawSprite(TextureManager::GetSingleton()->Get("ship.png"), 200, 200, 100, 100);
}

void Entity::UpdateMovement(float _deltaTime)
{

}

void Entity::UpdateProgress(float _deltaTime)
{
}

void Entity::PredictMovement(int _outX, int _outY)
{
}

void Entity::MoveTo(int _x, int _y)
{
}

void Entity::CheckCollision()
{
}
