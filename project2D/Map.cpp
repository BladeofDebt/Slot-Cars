#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "tinyxml2.h"
#include "Map.h"
#include <vector>

Map::Map()
{
	mp_tileLayer = nullptr;
	mp_textures = nullptr;

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

		std::vector<tinyxml2::XMLElement*> layers;

		for (tinyxml2::XMLElement* iter = root->FirstChildElement(); iter != nullptr; iter = iter->NextSiblingElement())
		{
			if (strcmp(iter->Name(), "layer"))
			{
				layers.push_back(iter);
			}
		}

		m_layers = layers.size();
		mp_tileLayer = new TileLayer[m_layers];

		for (int i = 0; i < m_layers; i++)
		{
			mp_tileLayer[i].m_width = m_width;
			mp_tileLayer[i].m_depth = m_depth;

			std::string data = layers[i]->FirstChildElement()->GetText();

			mp_tileLayer[i].mp_tile = new Tile*[m_width];

			for (int x = 0; x < m_width; x++)
			{
				mp_tileLayer[i].mp_tile[x] = new Tile[m_depth];
			}
		}
	}
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
	return mp_tileLayer[a_layer].mp_tile[a_x][a_y];
}

int Map::GetWidth() const
{
	return m_width;
}

int Map::GetDepth() const
{
	return m_depth;
}

void Map::Draw(const aie::Renderer2D& a_render)
{
}
