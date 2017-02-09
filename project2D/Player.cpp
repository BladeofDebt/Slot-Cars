#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Player.h"
#include "Map.h"
#include <Input.h>

//#include<iostream>

Player::Player(Map * _map, EntityTeam _team, InputSet _inputSet)
	: Entity(_map, EntityID::Player, _team), m_inputSet(_inputSet)
{
}

Player::~Player()
{
}

void Player::Update(float a_deltatime)
{
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
