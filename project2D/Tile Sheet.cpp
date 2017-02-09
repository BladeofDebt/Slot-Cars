#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Tile Sheet.h"

#include "../bootstrap/Texture.h"

TileSheet::TileSheet()
{
	m_startId = -1;
	mp_texture = nullptr;
}

TileSheet::~TileSheet()
{
	if (mp_texture)
	{
		delete mp_texture;
	}
}
