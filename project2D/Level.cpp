#include "Level.h"
#include "Map.h"

Level::Level()
{
	m_map = new Map();
}

Level::~Level()
{
	delete m_map;
}

void Level::Update(float a_deltatime)
{
}

void Level::Draw(aie::Renderer2D * _renderer)
{
}
