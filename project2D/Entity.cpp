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
#include "Level.h"
#include "Map.h"
#include "Tile.h"

const unsigned int Entity::m_defaultColor = (255 << 24) + (255 << 16) + (255 << 8) + 255;

Entity::Entity(Level* _level, EntityID _id, EntityTeam _team)
	: m_level(_level), m_id(_id), m_team(_team), m_x(), m_y(), m_dir(0), m_color(m_defaultColor), m_progress(0), m_speed(1), m_turn(0), m_active(false)
{
}

Entity::~Entity()
{
}

void Entity::Draw(aie::Renderer2D * _renderer)
{
	if (!m_active) { return; }

	float newX, newY;
	m_level->m_map->TileToWorld(m_x, m_y, newX, newY);
	float width = m_level->m_map->GetTileWidth();
	float height = m_level->m_map->GetTileHeight();

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

		CalcMovement();
		// Collision
	}
}

void Entity::CalcMovement()
{
	int FDirX, FDirY;
	DirToXYOffset(FDirX, FDirY);

	int facingX = m_x + FDirX;
	int facingY = m_y + FDirY;
	int facingID = m_level->m_map->GetTile(0, facingX, facingY).GetTileID();

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

// Clamps m_dir to 0-359 spectrum
void Entity::DirWrap()
{
	DirWrap(m_dir);
}

// Clamps Dir to 0-359 spectrum
void Entity::DirWrap(int & _dir)
{
	while (_dir >= 360) _dir -= 360;
	while (_dir <= 0) _dir += 360;
}

// Expects m_dir to be in 90 increments and clamped to 0-359 
void Entity::DirToXYOffset(int & _outX, int & _outY)
{
	DirToXYOffset(m_dir, _outX, _outY);
}

// Expects _dir to be in 90 increments and clamped to 0-359 
void Entity::DirToXYOffset(int & _dir, int & _outX, int & _outY)
{
	switch (_dir)
	{
	case 0:
		_outX = 1; _outY = 0;
		break;
	case 90:
		_outX = 0; _outY = -1;
		break;
	case 180:
		_outX = 1; _outY = 0;
		break;
	case 270:
		_outX = -1; _outY = 0;
		break;
	default:
		_outX = 0; _outY = 0;
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
