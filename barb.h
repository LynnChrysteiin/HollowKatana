#ifndef _BARB_H_
#define _BARB_H_

#include "animation.h"
#include "collision_box.h"

class Barb
{
private:
	enum class Stage
	{
		IDLE,
		AIM,
		DASH,
		BREAK,
	};

private:
	const float SPEED_DASH = 1500.0f;

private:
	Timer timer_idle;
	Timer timer_aim;
	int diff_period = 0;
	bool is_valid = true;
	float total_delta_time = 0.0f;

	Vec2 velocity;
	Vec2 base_position;
	Vec2 current_position;

	Animation animation_loose;
	Animation animation_break;
	Animation* current_animation = nullptr;

	Stage stage = Stage::IDLE;
	CollisionBox* collision_box = nullptr;

private:
	void on_break();

public:
	Barb();
	~Barb();

	void on_update(float delta);
	void on_render();
	void set_position(const Vec2& position);
	bool check_valid() const;
};

#endif // !_BARB_H_