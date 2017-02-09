#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Level.h"

#include "Map.h"
#include "TextureManager.h"
#include "Entity.h"
#include "Player.h"

Level::Level()
{
	m_map = new Map("Ze Mountains.tmx");

	TextureManager* tm = TextureManager::GetSingleton();
	std::string name;
	tm->LoadTexture("./textures/ship.png", name);

	Player* player1 = new Player(m_map, EntityTeam::Player1,
		InputSet{ aie::EInputCodes::INPUT_KEY_W, aie::EInputCodes::INPUT_KEY_A , aie::EInputCodes::INPUT_KEY_S , aie::EInputCodes::INPUT_KEY_D , aie::EInputCodes::INPUT_KEY_E });
	m_entities.push_back(player1);
}

Level::~Level()
{
	for (auto i = m_entities.begin(); i != m_entities.end(); i++)
		delete *i;

	if (m_map != nullptr)
		delete m_map;
}

void Level::Start()
{
}

void Level::Update(float a_deltatime)
{
	for each(Entity* entity in m_entities)
	{
		entity->Update(a_deltatime);
	}
}

void Level::Draw(aie::Renderer2D * _renderer)
{
	m_map->Draw(*_renderer);
}
