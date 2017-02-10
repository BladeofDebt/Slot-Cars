#include "Score Board.h"

#include "../bootstrap/Renderer2D.h"
#include "../bootstrap/Font.h"

#include <stdlib.h>

int ScoreBoard::m_player[2] = { 0, 0 };

void ScoreBoard::IncrementScore(int a_player)
{
	++m_player[a_player];
}

void ScoreBoard::Draw(aie::Font& a_font, aie::Renderer2D& a_render, unsigned int a_screenWidth, unsigned int a_screenHeight)
{
	char scoreString[10];

	itoa(m_player[0], scoreString, 10);

	a_render.drawText(&a_font, scoreString, 0.0f, a_screenHeight - 30.0f);

	itoa(m_player[1], scoreString, 10);

	a_render.drawText(&a_font, scoreString, a_screenWidth - 60.0f, a_screenHeight - 30.0f);
}
