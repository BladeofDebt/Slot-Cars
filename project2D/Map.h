#pragma once

#include "Tile Layer.h"
#include "../bootstrap/Texture.h"
#include "../bootstrap/Renderer2D.h"

class Map
{
private:
	int m_width;
	int m_depth;
	int m_layers;

	TileLayer* mp_tileLayer;

	aie::Texture* mp_textures;
protected:

public:
	Map();
	Map(const char* a_fileName);
	~Map();

	Tile& GetTile(int a_layer, int a_x, int a_y);

	int GetWidth() const;
	int GetDepth() const;

	void Draw(const aie::Renderer2D& a_render);
};