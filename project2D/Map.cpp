#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "tinyxml2.h"
#include "Map.h"
#include <vector>
#include <string>

#include "Tile Layer.h"
#include "Tile Sheet.h"
#include "Tile.h"

#include "../bootstrap/Renderer2D.h"
#include "../bootstrap/Texture.h"

Map::Map()
{
	mp_tileLayer = nullptr;
	mp_tileSheet = nullptr;

	m_width = -1;
	m_depth = -1;
	m_layers = -1;
}
Map::Map(const char* a_fileName)
{
	tinyxml2::XMLDocument document;

	tinyxml2::XMLError xmlError = document.LoadFile(a_fileName);

	if (xmlError == tinyxml2::XMLError::XML_SUCCESS)
	{
		tinyxml2::XMLElement* root = document.FirstChildElement();

		m_width = root->IntAttribute("width");
		m_depth = root->IntAttribute("height");
		m_tileWidth = root->FloatAttribute("tilewidth");
		m_tileHeight = root->FloatAttribute("tileheight");

		std::vector<tinyxml2::XMLElement*> layers;
		std::vector<tinyxml2::XMLElement*> tilesheets;

		for (tinyxml2::XMLElement* iter = root->FirstChildElement(); iter != nullptr; iter = iter->NextSiblingElement())
		{
			if (!strcmp(iter->Name(), "layer"))
			{
				layers.push_back(iter);
			}
			else if (!strcmp(iter->Name(), "tileset"))
			{
				tilesheets.push_back(iter);
			}
		}

#pragma region Tile Data Importing
		m_layers = layers.size();
		mp_tileLayer = new TileLayer[m_layers];

		for (int i = 0; i < m_layers; i++)
		{
			mp_tileLayer[i].m_width = m_width;
			mp_tileLayer[i].m_depth = m_depth;

			mp_tileLayer[i].mp_tile = new Tile*[m_width];

			for (int x = 0; x < m_width; x++)
			{
				mp_tileLayer[i].mp_tile[x] = new Tile[m_depth];
			}

			std::string data = layers[i]->FirstChildElement()->GetText();

			int index = 0;

			while (true)
			{
				index = data.find('\n');

				if (index != -1)
				{
					data.erase(index, 1);
				}
				else
				{
					break;
				}
			}

			for (int y = 0; y < m_depth; y++)
			{
				for (int x = 0; x < m_width; x++)
				{
					index = data.find(',');

					std::string numString;

					if (index != -1)
					{
						numString = data.substr(0, index);
						data.erase(0, index + 1);
					}
					else
					{
						numString = data;
						data.clear();
					}

					mp_tileLayer[i].mp_tile[x][y].m_tileId = atoi(numString.c_str());
				}
			}
		}
#pragma endregion

#pragma region Tile Sheet Loading
		m_tileSheetNum = tilesheets.size();
		mp_tileSheet = new TileSheet[m_tileSheetNum];

		for (int i = 0; i < m_tileSheetNum; i++)
		{
			mp_tileSheet[i].m_startId = tilesheets[i]->IntAttribute("firstgid");
			mp_tileSheet[i].m_columns = tilesheets[i]->IntAttribute("columns");

			mp_tileSheet[i].mp_texture = new aie::Texture(std::string("./textures/").append(tilesheets[i]->FirstChildElement()->Attribute("source")).c_str());
			mp_tileSheet[i].m_tileWidth = tilesheets[i]->FloatAttribute("tilewidth");
			mp_tileSheet[i].m_tileHeight = tilesheets[i]->FloatAttribute("tileheight");
		}
#pragma endregion
	}
}

Map::~Map()
{
	if (mp_tileSheet)
	{
		delete[] mp_tileSheet;
	}

	if (mp_tileLayer)
	{
		delete[] mp_tileLayer;
	}
}

Tile& Map::GetTile(int a_layer, int a_x, int a_y)
{
	return mp_tileLayer[a_layer].mp_tile[a_x][a_y - 1];
}

Tile& Map::GetTile(int a_layer, float a_xPos, float a_yPos)
{
	return mp_tileLayer[a_layer].mp_tile[(int)(a_xPos / m_tileWidth)][(m_depth - (int)(a_yPos / m_tileHeight))];
}

int Map::GetWidth() const
{
	return m_width;
}

int Map::GetDepth() const
{
	return m_depth;
}

float Map::GetTileWidth() const
{
	return m_tileWidth;
}

float Map::GetTileHeight() const
{
	return m_tileHeight;
}

int Map::GetLayerCount() const
{
	return m_layers;
}

void Map::TileToWorld(const float a_tileX, const float a_tileY, float & a_outWorldX, float & a_outWorldY) const
{
	a_outWorldX = a_tileX * m_tileWidth;
	a_outWorldY = (m_depth - a_tileY) * m_tileHeight;
}

void Map::Draw(aie::Renderer2D& a_render) const
{
	for (int i = 1; i < m_layers; i++)
	{
		for (int x = 0; x < m_width; x++)
		{
			for (int y = 0; y < m_depth; y++)
			{
				int tileId = mp_tileLayer[i].mp_tile[x][y].m_tileId;

				if (tileId != 0)
				{
					int tileSheetIndex = -1;

					for (int j = 0; j < m_tileSheetNum; j++)
					{
						++tileSheetIndex;
						if (mp_tileSheet[j].m_startId > tileId)
						{
							--tileSheetIndex;
							break;
						}
					}

					int trueIndex = tileId - mp_tileSheet[tileSheetIndex].m_startId;

					int xPos, yPos;

					xPos = trueIndex % mp_tileSheet[tileSheetIndex].m_columns;
					yPos = trueIndex / mp_tileSheet[tileSheetIndex].m_columns;

					float tileSheetWidth = (float)mp_tileSheet[tileSheetIndex].mp_texture->getWidth();
					float tileSheetHeight = (float)mp_tileSheet[tileSheetIndex].mp_texture->getHeight();

					float tileWidth = mp_tileSheet[tileSheetIndex].m_tileWidth;
					float tileHeight = mp_tileSheet[tileSheetIndex].m_tileHeight;

					float u = xPos * (tileWidth / tileSheetWidth);
					float v = yPos * (tileHeight / tileSheetHeight);
					float w = tileWidth / tileSheetWidth;
					float h = tileHeight / tileSheetHeight;

					a_render.setUVRect(u, v, w, h);
					a_render.drawSprite(mp_tileSheet[tileSheetIndex].mp_texture, x * m_tileWidth + (m_tileWidth / 2.0f), (m_depth - y) * m_tileHeight - (m_tileHeight / 2.0f), m_tileWidth, m_tileHeight);
				}
			}
		}
	}
	a_render.setUVRect(0, 0, 1, 1);
}
