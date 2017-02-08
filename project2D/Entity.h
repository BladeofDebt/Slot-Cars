#pragma once

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
	Entity();
	~Entity();

	// Move on grid
	void UpdateMovement(float _deltaTime);

	EntityID m_id;
	EntityTeam m_team;
	int m_x, m_y;
	int m_dirX, m_dirY;
	int m_turn; // -1=left, 0=forwards, 1=right
	float m_speed; //
	float m_progress; // += deltaT*speed each update, to next tile jump
};
