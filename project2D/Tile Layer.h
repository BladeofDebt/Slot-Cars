#pragma once

#include "Tile.h"

class TileLayer
{
private:
	int m_width;
	int m_depth;

	Tile** mp_tile;
protected:

public:
	TileLayer();
	~TileLayer();

	int GetWidth();
	int GetDepth();
};