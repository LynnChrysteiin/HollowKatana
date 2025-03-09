#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "animation.h"
#include "collision_box.h"
#include "state_machine.h"
#include "vec2.h"

#include <graphics.h>
#include <string.h>
#include <unordered_map>

class Character
{
protected:
	struct AnimationGroup
	{
		Animation left;
		Animation right;
	};

protected:
	const float FLOOR_Y = 620;										// 地板高度
	const float GRAVITY = 980 * 2;									// 重力加速度

protected:
	Vec2 position;													// 位置
	Vec2 velocity;													// 速度
	int hp = 10;													// 生命值
	float logic_height = 0;											// 逻辑高度
	bool is_facing_left = true;										// 是否朝向左边
	bool enable_gravity = true;										// 是否启用重力
	bool is_invulnerable = false;									// 是否无敌状态
	StateMachine state_machine;										// 角色状态机	
	Timer timer_invulnerable_blink;									// 无敌状态闪烁计时器
	Timer timer_invulnerable_status;								// 无敌状态计时器
	bool is_blink_invisible = false;								// 是否处于闪烁帧
	CollisionBox* hit_box = nullptr;								// 攻击碰撞箱
	CollisionBox* hurt_box = nullptr;								// 受击碰撞箱
	AnimationGroup* current_animation = nullptr;					// 当前动画
	std::unordered_map<std::string, AnimationGroup> animation_pool;	// 角色动画池

public:
	Character();
	~Character();

	void decrease_hp();
	int get_hp() const;
	void set_position(const Vec2& position);
	const Vec2& get_position() const;
	void set_velocity(const Vec2& velocity);
	const Vec2& get_velocity() const;
	Vec2 get_logic_center() const;
	void set_gravity_enabled(bool flag);
	CollisionBox* get_hit_box();
	CollisionBox* get_hurt_box();
	bool is_on_floor() const;
	float get_floor_y() const;
	void make_invulnerable();
	void switch_state(const std::string& id);
	void set_animation(const std::string& id);

	virtual void on_input(const ExMessage& msg);
	virtual void on_update(float delta);
	virtual void on_render();
	virtual void on_hurt();
};

#endif // !_CHARACTER_H_
