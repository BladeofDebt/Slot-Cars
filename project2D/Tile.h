#pragma once

class Tile
{
private:
	friend class Map;

	int m_tileId;
protected:

public:
	int GetTileID();
};