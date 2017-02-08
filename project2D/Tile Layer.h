#pragma once

#include "Tile.h"

class TileLayer
{
private:
	friend class Map;

	int m_width;
	int m_depth;

	Tile** mp_tile;
protected:

public:
	~TileLayer();

	int GetWidth();
	int GetDepth();
};