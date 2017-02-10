#pragma once

class Level;
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
	Entity(Level* _level, EntityID _id, EntityTeam _team);
	~Entity();

	void Draw(aie::Renderer2D* _renderer);
	// Move on grid
	void UpdateMovement(float _deltaTime);

	virtual void Update(float a_deltatime);
	virtual void OnCollision(Entity * a_entity) = 0;
	virtual void SetTurn(int _newTurn);

	void CalcMovement();
	void CheckCollision(Entity * a_entity);
	void TryCollision();
	void DirWrap();
	int DirWrap(int _dir) const;
	void DirToXYOffset(int& _outX, int& _outY);
	void DirToXYOffset(int& _dir, int& _outX, int& _outY) const;

	Level* m_level;
	aie::Texture* m_texture;
	EntityID m_id;
	EntityTeam m_team;
	int m_x, m_y;
	int m_dir;
	int m_turn; // -1=left, 0=forwards, 1=right
	float m_speed; //
	float m_progress; // += deltaT*speed each update, to next tile jump
	unsigned int m_color;
	const static unsigned int m_defaultColor;
	bool m_activeGet;
	bool m_activeSet;
	bool m_resetsOnTurnSuccess; // Resets Turn to 0 on successful turn

protected:
	static unsigned int CToIColor(const char & a, const char& r, const char&  g, const char&  b);
	int GetTileColID(int _x, int _y) const;
	bool TryMoveInDir(const int& _dir);
	int GetTurnedDir() const;

};
