#pragma once

namespace aie
{
	class Font;
	class Renderer2D;
}

class ScoreBoard
{
private:
	static int m_player[2];
	static unsigned int m_colors[3];
protected:

public:
	static void IncrementScore(int a_player);
	static void Draw(aie::Font& a_font, aie::Renderer2D& a_render, unsigned int a_screenWidth, unsigned int a_screenHeight);
	static void SetColor(int a_player, unsigned int a_color);
};
