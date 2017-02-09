#pragma once

#include <vector>

namespace aie { class Renderer2D; }
class Map;
class Entity;

class Level
{
public:
	Level();
	~Level();

	void Start();
	void Update(float a_deltatime);
	void Draw(aie::Renderer2D* _renderer);

	std::vector<Entity*> m_entities;
	Map* m_map;
};
