#include "Tile Layer.h"

TileLayer::~TileLayer()
{
	if (mp_tile)
	{
		for (int i = 0; i < m_width; i++)
		{
			if (mp_tile[i])
			{
				delete mp_tile[i];
			}
		}

		delete mp_tile;
	}
}

int TileLayer::GetWidth()
{
	return m_width;
}

int TileLayer::GetDepth()
{
	return m_depth;
}
