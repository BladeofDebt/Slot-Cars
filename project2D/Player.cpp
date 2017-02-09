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
	m_activeSet = true;
	m_activeGet = true;

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
	m_lowSpeed = 0.75f;
	m_defaultSpeed = 1.5f;
	m_highSpeed = 3.0f;
	m_deathSpeed = 15.0f;
	m_speedCooldown = 0;
	m_speedCooldownMax = 1;
	m_x = 3;
	m_y = 3;
}

Player::~Player()
{
}

void Player::Update(float a_deltatime)
{
	if (!m_activeGet) { return; }

	Entity::Update(a_deltatime);
	HandleInput(a_deltatime);
}

void Player::OnCollision(Entity * a_entity)
{
	if (!m_activeGet) { return; }

	switch (a_entity->m_id)
	{
	case EntityID::Bullet:
		//m_activeSet = false; //BOOOOOORING
		m_speed = m_deathSpeed;
		m_speedCooldown = 0.3f;
		break;
	default:
		break;
	}
}


void Player::HandleInput(float a_deltatime)
{
	aie::Input* _input = aie::Input::getInstance();

	//Speed Control
	if (m_speedCooldown > 0)
		m_speedCooldown -= a_deltatime;

	if (m_speedCooldown <= 0)
	{
		bool sUp = _input->isKeyDown(m_inputSet.accelerate);
		bool sDown = _input->isKeyDown(m_inputSet.deccelerate);

		if (sUp)
		{ // Speed up
			m_turn = 0;
			m_speed = m_highSpeed;
			m_speedCooldown = m_speedCooldownMax;
		}
		else if (sDown)
		{ // Speed down
			m_speed = m_lowSpeed;
			m_speedCooldown = m_speedCooldownMax;
		}
		else
		{  // Speed normalise
			m_speed = m_defaultSpeed;
		}
	}

	//Turn Control
	if (_input->isKeyDown(m_inputSet.left))
	{
		m_turn = -1;
	}
	else if (_input->isKeyDown(m_inputSet.right))
	{
		m_turn = 1;
	}
	//Fire
	if (_input->isKeyDown(m_inputSet.fire))
	{
		Fire();
	}
}

void Player::Fire()
{
	if (!m_bullet->m_activeGet) {
		m_bullet->m_activeSet = true;
		m_bullet->m_x = m_x;
		m_bullet->m_y = m_y;
		m_bullet->m_dir = m_dir;
		m_bullet->m_progress = m_progress;
		m_bullet->m_turn = m_turn;
	}
}
