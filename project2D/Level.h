#pragma once

class Renderer2D;

class Level
{
public:
	Level();
	~Level();

	void Start();
	void Update(float a_deltatime);
	void Draw(Renderer2D* _renderer);
};
