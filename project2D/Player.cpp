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

const InputSet Player::PLAYER1_INPUTSET = InputSet{ aie::EInputCodes::INPUT_KEY_W,	aie::EInputCodes::INPUT_KEY_A,		aie::EInputCodes::INPUT_KEY_S,		aie::EInputCodes::INPUT_KEY_D,		aie::EInputCodes::INPUT_KEY_F,		aie::EInputCodes::INPUT_KEY_G };
const InputSet Player::PLAYER2_INPUTSET = InputSet{ aie::EInputCodes::INPUT_KEY_UP,	aie::EInputCodes::INPUT_KEY_LEFT,	aie::EInputCodes::INPUT_KEY_DOWN,	aie::EInputCodes::INPUT_KEY_RIGHT,	aie::EInputCodes::INPUT_KEY_KP_0,	aie::EInputCodes::INPUT_KEY_KP_DECIMAL };

Player::Player(Level * _level, EntityTeam _team, Bullet* a_bullet)
	: Entity(_level, EntityID::Player, _team), m_bullet(a_bullet)
{
	m_activeSet = true;
	m_activeGet = true;
	m_resetsOnTurnSuccess = true;

	switch (_team)
	{
	case EntityTeam::Player1:
		m_inputSet = PLAYER1_INPUTSET;
		m_slowColor = CToIColor(255, 150, 0, 0);
		m_normalColor = CToIColor(255, 200, 0, 0);
		m_boostColor = CToIColor(255, 255, 0, 0);
		m_x = 3; m_y = 3; m_dir = 0;
		break;
	case EntityTeam::Player2:
		m_inputSet = PLAYER2_INPUTSET;
		m_slowColor = CToIColor(255, 0, 0, 150);
		m_normalColor = CToIColor(255, 0, 0, 200);
		m_boostColor = CToIColor(255, 0, 0, 255);
		m_x = 30; m_y = 3; m_dir = 180;
		break;
	default:
		break;
	}
	m_color = m_normalColor;

	TextureManager* tm = TextureManager::GetSingleton();

	m_textureForward = tm->Get("car_forward.png");
	m_textureLeft = tm->Get("car_turnL.png");
	m_textureRight = tm->Get("car_turnR.png");
	m_texture = m_textureForward;
	m_lowSpeed = 0.75f;
	m_normalSpeed = 2.0f;
	m_highSpeed = 5.0f;
	m_deathSpeed = 15.0f;
	m_deathSpeedMax = 1.0f;
	m_speedCooldown = 0;
	m_speedCooldownMax = 0.5f;
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
		m_speed = m_deathSpeed;
		m_speedCooldown = m_deathSpeedMax;
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
		if (_input->isKeyDown(m_inputSet.boost))
		{ // Speed up
			m_speed = m_highSpeed;
			m_speedCooldown = m_speedCooldownMax;
			m_color = m_boostColor;
		}
		else if (_input->isKeyDown(m_inputSet.slowDown))
		{ // Speed down
			m_speed = m_lowSpeed;
			m_speedCooldown = m_speedCooldownMax;
			m_color = m_slowColor;
		}
		else
		{  // Speed normalise
			m_speed = m_normalSpeed;
			m_color = m_normalColor;
		}
	}

	//Turn Control
	if (_input->isKeyDown(m_inputSet.align))
	{
		SetTurn(0);
	}
	else if (_input->isKeyDown(m_inputSet.left))
	{
		SetTurn(-1);
	}
	else if (_input->isKeyDown(m_inputSet.right))
	{
		SetTurn(1);
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
		m_bullet->SetTurn(m_turn);
	}
}

void Player::SetTurn(int _newTurn)
{
	if (m_turn != _newTurn) {
		Entity::SetTurn(_newTurn);
		switch (m_turn)
		{
		case -1:
			m_texture = m_textureLeft;
			break;
		case 0:
			m_texture = m_textureForward;
			break;
		case 1:
			m_texture = m_textureRight;
			break;
		default:
			break;
		}
	}
}
