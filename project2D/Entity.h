#pragma once

class Map;
namespace aie { class Texture; class Renderer2D; }

enum class EntityID
{
	Invalid,
	Player,
	Bullet,
	Length
};

enum class EntityTeam
{
	Invalid,
	Player1,
	Player2,
	Length
};

class Entity
{
public:
	Entity(Map* _map, EntityID _id, EntityTeam _team);
	~Entity();

	void Draw(aie::Renderer2D* _renderer);
	// Move on grid
	void UpdateMovement(float _deltaTime);

	virtual void Update(float a_deltatime) = 0;

	void UpdateProgress(float _deltaTime);
	void PredictMovement(int _outX, int _outY);
	void MoveTo(int _x, int _y);
	void CheckCollision();

	Map* m_map;
	aie::Texture* m_texture;
	EntityID m_id;
	EntityTeam m_team;
	int m_x, m_y;
	int m_dirX, m_dirY;
	int m_turn; // -1=left, 0=forwards, 1=right
	float m_speed; //
	float m_progress; // += deltaT*speed each update, to next tile jump
};
