#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Player.h"
#include "Map.h"
#include <Input.h>
#include "TextureManager.h"

//#include<iostream>

const InputSet Player::PLAYER1_INPUTSET = InputSet{ aie::EInputCodes::INPUT_KEY_W,	aie::EInputCodes::INPUT_KEY_A,		aie::EInputCodes::INPUT_KEY_S,		aie::EInputCodes::INPUT_KEY_D,		aie::EInputCodes::INPUT_KEY_E };
const InputSet Player::PLAYER2_INPUTSET = InputSet{ aie::EInputCodes::INPUT_KEY_UP,	aie::EInputCodes::INPUT_KEY_LEFT,	aie::EInputCodes::INPUT_KEY_DOWN,	aie::EInputCodes::INPUT_KEY_RIGHT,	aie::EInputCodes::INPUT_KEY_KP_0 };

Player::Player(Map * _map, EntityTeam _team)
	: Entity(_map, EntityID::Player, _team)
{
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

void Player::HandleInput()
{
	if (aie::Input::getInstance()->isKeyDown(m_inputSet.accelerate))
	{
		// test
		// std::cout << "Player 1 accelerate input test" << std::endl;


	}
}

void Player::Fire()
{
}
