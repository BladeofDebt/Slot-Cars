#pragma once
#include <Renderer2D.h>
class aie::Renderer2D;
class Map;

class Level
{
public:
	Level();
	~Level();

	void Update(float a_deltatime);
	void Draw(aie::Renderer2D* _renderer);

	Map* m_map;

};
