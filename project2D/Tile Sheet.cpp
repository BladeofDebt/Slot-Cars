#include "Tile Sheet.h"

#include "../bootstrap/Texture.h"

TileSheet::TileSheet()
{
	m_startId = -1;
	mp_texture = nullptr;
}

TileSheet::~TileSheet()
{
	if (mp_texture)
	{
		delete mp_texture;
	}
}
