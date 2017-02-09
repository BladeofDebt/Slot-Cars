#pragma once

class TileLayer;
class TileSheet;
class Tile;

namespace aie
{
	class Renderer2D;
}

class Map
{
private:
	int m_width;
	int m_depth;
	int m_layers;
	int m_tileSheetNum;

	TileLayer* mp_tileLayer;
	TileSheet* mp_tileSheet;

	float m_tileWidth;
	float m_tileHeight;
protected:

public:
	Map();
	Map(const char* a_fileName);
	~Map();

	Tile& GetTile(int a_layer, int a_x, int a_y);
	Tile& GetTile(int a_layer, float a_xPos, float a_yPos);

	int GetWidth() const;
	int GetDepth() const;
	float GetTileWidth() const;
	float GetTileHeight() const;
	int GetLayerCount() const;
	void TileToWorld(const int a_tileX, const int a_tileY, float& a_outWorldX, float& a_outWorldY) const;

	void Draw(aie::Renderer2D& a_render) const;
};