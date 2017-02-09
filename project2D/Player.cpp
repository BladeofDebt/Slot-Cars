#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Player.h"
#include"Bullet.h"
#include "Map.h"
#include <Input.h>
#include "TextureManager.h"

const InputSet Player::PLAYER1_INPUTSET = InputSet{ aie::EInputCodes::INPUT_KEY_W,	aie::EInputCodes::INPUT_KEY_A,		aie::EInputCodes::INPUT_KEY_S,		aie::EInputCodes::INPUT_KEY_D,		aie::EInputCodes::INPUT_KEY_E };
const InputSet Player::PLAYER2_INPUTSET = InputSet{ aie::EInputCodes::INPUT_KEY_UP,	aie::EInputCodes::INPUT_KEY_LEFT,	aie::EInputCodes::INPUT_KEY_DOWN,	aie::EInputCodes::INPUT_KEY_RIGHT,	aie::EInputCodes::INPUT_KEY_KP_0 };

Player::Player(Level * _level, EntityTeam _team, Bullet* a_bullet)
	: Entity(_level, EntityID::Player, _team), m_bullet(a_bullet)
{
	m_active = true;

	switch (_team)
	{
	case EntityTeam::Player1:
		m_inputSet = PLAYER1_INPUTSET;
		m_color = CToIColor(255, 255, 0, 0);
		break;
	case EntityTeam::Player2:
		m_inputSet = PLAYER1_INPUTSET;
		m_color = CToIColor(255, 0, 0, 255);
		break;
	default:
		break;
	}
	m_texture = TextureManager::GetSingleton()->Get("car.png");
	m_speed = 4;
	m_x = 3;
	m_y = 3;
}

Player::~Player()
{
}

void Player::Update(float a_deltatime)
{
	if (!m_active) { return; }

	HandleInput();
	Entity::UpdateMovement(a_deltatime);
}

void Player::OnCollision(Entity * m_entity)
{
}


void Player::HandleInput()
{
	if (aie::Input::getInstance()->isKeyDown(m_inputSet.accelerate))
	{

	}
	if (aie::Input::getInstance()->isKeyDown(m_inputSet.deccelerate))
	{

	}
	if (aie::Input::getInstance()->isKeyDown(m_inputSet.left))
	{

	}
	if (aie::Input::getInstance()->isKeyDown(m_inputSet.right))
	{

	}
	if (aie::Input::getInstance()->isKeyDown(m_inputSet.fire))
	{
		Fire();
	}
}

void Player::Fire()
{
	m_bullet->m_x = m_x;
	m_bullet->m_y = m_y;
	m_bullet->m_dir = m_dir;
	m_bullet->m_active = true;
}
