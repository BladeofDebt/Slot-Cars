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
	: m_level(_level), m_id(_id), m_team(_team), m_x(), m_y(), m_dir(0), m_color(m_defaultColor), m_progress(0), m_speed(1), m_turn(0), m_activeGet(false), m_activeSet(false)
{
}

Entity::~Entity()
{
}

void Entity::Draw(aie::Renderer2D * _renderer)
{
	if (!m_activeGet) { return; }

	float newX, newY;
	m_level->m_map->TileToWorld(m_x, m_y, newX, newY);
	float width = m_level->m_map->GetTileWidth();
	float height = m_level->m_map->GetTileHeight();

	_renderer->setRenderColour(m_color);
	_renderer->drawSprite(m_texture, newX + width * 0.5f, newY + height * 0.5f, width, height, (m_dir * 3.1415926535897) / 180.0f);
	_renderer->setRenderColour(m_defaultColor);
}

void Entity::Update(float a_deltatime)
{
	TryCollision();
	m_activeGet = m_activeSet;
	if (m_activeGet)
		UpdateMovement(a_deltatime);
}

void Entity::UpdateMovement(float _deltaTime)
{
	m_progress += _deltaTime * m_speed;

	while (m_progress > 1)
	{
		m_progress -= 1;

		CalcMovement();

		TryCollision();
	}
}

void Entity::CalcMovement()
{
	if (TryMoveInDir(GetTurnedDir())) {}		// Move Turn Dir
	else if (TryMoveInDir(DirWrap(m_dir))) {}			// Move Forewards
	else if (TryMoveInDir(DirWrap(m_dir - 90))) {}	// Turn Move
	else if (TryMoveInDir(DirWrap(m_dir + 90))) {}	// Turn Move
	else	TryMoveInDir(DirWrap(m_dir + 180)); {} // Move Backwards
}

void Entity::CheckCollision(Entity* a_entity)
{
	if (a_entity->m_x == m_x && a_entity->m_y == m_y)
	{
		OnCollision(a_entity);
		a_entity->OnCollision(this);
	}
}

void Entity::TryCollision()
{
	for (auto i = m_level->m_entities.begin(); i != m_level->m_entities.end(); i++)
	{
		if ((*i)->m_team != m_team && (*i)->m_activeGet)
			CheckCollision((*i));
	}
}

// Clamps m_dir to 0-359 spectrum
void Entity::DirWrap()
{
	m_dir = DirWrap(m_dir);
}

// Clamps Dir to 0-359 spectrum
int Entity::DirWrap(int _dir) const
{
	while (_dir >= 360) _dir -= 360;
	while (_dir < 0) _dir += 360;
	return _dir;
}

// Expects m_dir to be in 90 increments and clamped to 0-359 
void Entity::DirToXYOffset(int & _outX, int & _outY)
{
	DirToXYOffset(m_dir, _outX, _outY);
}

// Expects _dir to be in 90 increments and clamped to 0-359 
void Entity::DirToXYOffset(int & _dir, int & _outX, int & _outY) const
{
	switch (_dir)
	{
	case 0:
		_outX = 1; _outY = 0;
		break;
	case 90:
		_outX = 0; _outY = 1;
		break;
	case 180:
		_outX = -1; _outY = 0;
		break;
	case 270:
		_outX = 0; _outY = -1;
		break;
	default:
		_outX = 0; _outY = 0;
		break;
	}
}

unsigned int Entity::CToIColor(const char & a, const char & r, const char & g, const char & b)
{
	return ((b & 0xFF) << 24) | //alpha
		(((int)g & 0xFF) << 16) | //red
		(((int)r & 0xFF) << 8) | //green
		(((int)a & 0xFF) << 0); //blue
}

int Entity::GetTileColID(int _x, int _y) const
{
	int width = m_level->m_map->GetWidth();
	int height = m_level->m_map->GetDepth();
	if (_x >= width) _x = width - 1;
	if (_y >= height) _y = height - 1;
	return m_level->m_map->GetTile(0, _x, _y).GetTileID();
}

bool Entity::TryMoveInDir(const int & _dir)
{
	int tryDir = DirWrap(_dir);

	int xOS, yOS;
	DirToXYOffset(tryDir, xOS, yOS);
	xOS = m_x + xOS;
	yOS = m_y + yOS;
	int tryID = GetTileColID(xOS, yOS);//GetTileColIDByDir(tryDir);

	if (tryID != 0)
		return false;
	else {
		// Empty space, so move
		m_dir = tryDir;
		m_x = xOS; m_y = yOS;
		return true;
	}
}

int Entity::GetTurnedDir() const
{
	int newDir = m_dir;
	switch (m_turn)
	{
	case -1:
		newDir += 90;
		break;
	case 0:
		break;
	case 1:
		newDir -= 90;
		break;
	default:
		break;
	}
	return DirWrap(newDir);
}
