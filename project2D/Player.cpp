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

// TODO : Remove after testing.
#include<iostream>

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
		m_inputSet = PLAYER2_INPUTSET;
		m_color = CToIColor(255, 0, 0, 255);
		break;
	default:
		break;
	}
	m_texture = TextureManager::GetSingleton()->Get("car.png");
}

Player::~Player()
{
}

void Player::Update(float a_deltatime)
{
	if (!m_active) { return; }

	Entity::UpdateMovement(a_deltatime);
	HandleInput();
}

void Player::OnCollision(Entity * a_entity)
{
	if (!m_active) { return; }

	//a_entity->m_active = false;
	// TODO : Remove after testing.

	if (a_entity->m_id == EntityID::Bullet)
		std::cout << "Bullet Collision" << std::endl;
	//else
		//std::cout << "Player Collided" << std::endl;
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
	m_bullet->m_active = true;
	m_bullet->m_x = m_x;
	m_bullet->m_y = m_y;
	m_bullet->m_dir = m_dir;
}
