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
#include "Map.h"
#include "Tile.h"

const unsigned int Entity::m_defaultColor = (255 << 24) + (255 << 16) + (255 << 8) + 255;

Entity::Entity(Map* _map, EntityID _id, EntityTeam _team)
	: m_map(_map), m_id(_id), m_team(_team), m_x(), m_y(), m_color(m_defaultColor), m_speed(1), m_active(false)
{
}

Entity::~Entity()
{
}

void Entity::Draw(aie::Renderer2D * _renderer)
{
	if (!m_active) { return; }

	float newX, newY;
	m_map->TileToWorld(m_x, m_y, newX, newY);
	float width = m_map->GetTileWidth();
	float height = m_map->GetTileHeight();

	_renderer->setRenderColour(m_color);
	_renderer->drawSprite(m_texture, newX + width * 0.5f, newY + height * 0.5f, width, height);
	_renderer->setRenderColour(m_defaultColor);
}

void Entity::UpdateMovement(float _deltaTime)
{
	UpdateProgress(_deltaTime);
}

void Entity::UpdateProgress(float _deltaTime)
{
	m_progress += _deltaTime * m_speed;
	while (m_progress > 1)
	{
		m_progress -= 1;

		int newX, newY;
		CalcMovement();
	}
}

void Entity::CalcMovement()
{
	int facingX = m_x;
	int facingY = m_y;
	int facingID = m_map->GetTile(0, facingX, facingY).GetTileID();

	switch (facingID)
	{
	case 0: // Empty space in front
		m_x = facingX;
		m_y = facingY;
		break;
	default:

		break;
	}
}

void Entity::CheckCollision(Entity* a_entity)
{
	if (a_entity->m_x == m_x && a_entity->m_y == m_y)
		OnCollision(a_entity);
}

void Entity::DirToXYOffset(const int & _dir, int & _outX, int & _outY)
{
	switch (_dir)
	{
	case 0:

		break;
	default:
		break;
	}
}

unsigned int Entity::CToIColor(const char & a, const char & r, const char & g, const char & b)
{
	return ((r & 0xFF) << 24) | //alpha
		(((int)g & 0xFF) << 16) | //red
		(((int)b & 0xFF) << 8) | //green
		(((int)a & 0xFF) << 0); //blue
}
