#pragma once

#include "../bootstrap/Renderer2D.h"
class Map;

class Level
{
	Map* mp_map;

public:
	Level();
	~Level();

	void Start();
	void Update(float a_deltatime);
	void Draw(aie::Renderer2D* _renderer);
};
