#include "Level.h"

#include "Map.h"

Level::Level()
{
	mp_map = new Map("Tilemap.tmx");
}

Level::~Level()
{
	if (mp_map)
	{
		delete mp_map;
	}
}

void Level::Start()
{
}

void Level::Update(float a_deltatime)
{
}

void Level::Draw(aie::Renderer2D * _renderer)
{
}
