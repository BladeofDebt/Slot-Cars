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
#include "Bullet.h"

Level::Level()
{
	m_map = new Map("Ze Mountains.tmx");

	TextureManager* tm = TextureManager::GetSingleton();
	tm->LoadTexture("./textures/car.png");
	tm->LoadTexture("./textures/bullet.png");

	// Initialize Entities
	Bullet* bullet1 = new Bullet(this, EntityTeam::Player1);
	m_entities.push_back(bullet1);

	Bullet* bullet2 = new Bullet(this, EntityTeam::Player2);
	m_entities.push_back(bullet2);

	Player* player1 = new Player(this, EntityTeam::Player1, bullet1);
	m_entities.push_back(player1);

	Player* player2 = new Player(this, EntityTeam::Player2, bullet2);
	m_entities.push_back(player2);
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
	for (auto i = m_entities.begin(); i != m_entities.end(); i++)
		(*i)->Update(a_deltatime);	
}

void Level::Draw(aie::Renderer2D * _renderer)
{
	m_map->Draw(*_renderer);

	for (auto i = m_entities.begin(); i != m_entities.end(); i++)
		(*i)->Draw(_renderer);
}
