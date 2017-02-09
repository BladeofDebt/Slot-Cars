#pragma once

#include <glm\vec3.hpp>

namespace aie
{
	class Texture;
}

class TileSheet
{
private:
	friend class Map;

	int m_startId;
	int m_columns;
	aie::Texture* mp_texture;

	float m_tileWidth, m_tileHeight;
protected:

public:
	TileSheet();
	~TileSheet();
};