#include "Score Board.h"

#include "../bootstrap/Renderer2D.h"
#include "../bootstrap/Font.h"

#include <stdlib.h>

#include "Player.h"
#include <iostream>

int ScoreBoard::m_player[2] = { 0, 0 };
unsigned int ScoreBoard::m_colors[3] = { Entity::m_defaultColor, 0, 0 };

void ScoreBoard::IncrementScore(int a_player)
{
	std::cout << a_player << "\n";
	++m_player[a_player];
}

void ScoreBoard::Draw(aie::Font& a_font, aie::Renderer2D& a_render, unsigned int a_screenWidth, unsigned int a_screenHeight)
{
	char scoreString[10];

	itoa(m_player[0], scoreString, 10);
	a_render.setRenderColour(m_colors[1]);
	a_render.drawText(&a_font, scoreString, 40.0f, a_screenHeight - 30.0f);
	a_render.setRenderColour(m_colors[0]);

	itoa(m_player[1], scoreString, 10);

	a_render.setRenderColour(m_colors[2]);
	a_render.drawText(&a_font, scoreString, a_screenWidth - 60.0f, a_screenHeight - 30.0f);
	a_render.setRenderColour(m_colors[0]);
}

void ScoreBoard::SetColor(int a_player, unsigned int a_color)
{
	m_colors[a_player] = a_color;
}
