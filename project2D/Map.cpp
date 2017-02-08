#include "Map.h"

Map::Map()
{
	mp_tileLayer = nullptr;
	mp_textures = nullptr;

	m_width = -1;
	m_depth = -1;
	m_layers = -1;
}
Map::Map(const char * a_fileName)
{

}

Map::~Map()
{
	if (mp_tileLayer)
	{
		delete mp_tileLayer;
	}

	if (mp_textures)
	{
		delete mp_textures;
	}
}

Tile& Map::GetTile(int a_layer, int a_x, int a_y)
{
	return mp_tileLayer[a_layer][a_x][a_y];
}

int Map::GetWidth() const
{
	return m_width;
}

int Map::GetDepth() const
{
	return m_depth;
}

void Map::Draw(const aie::Renderer2D & a_render)
{
}
