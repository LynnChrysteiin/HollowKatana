#ifndef _SWORD_H_
#define _SWORD_H_

#include "animation.h"
#include "collision_box.h"

class Sword
{
private:
	const float SPEED_MOVE = 1250.0f;

private:
	Vec2 position;
	Vec2 velocity;
	Animation animation;
	bool is_valid = true;
	CollisionBox *collision_box = nullptr;

public:
	Sword();
	Sword(const Vec2& position, bool move_left);
	~Sword();

	void on_update(float delta);
	void on_render();
	bool check_valid() const;
};

#endif // !_SWORD_H_