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
	const float FLOOR_Y = 620;										// �ذ�߶�
	const float GRAVITY = 980 * 2;									// �������ٶ�

protected:
	Vec2 position;													// λ��
	Vec2 velocity;													// �ٶ�
	int hp = 10;													// ����ֵ
	float logic_height = 0;											// �߼��߶�
	bool is_facing_left = true;										// �Ƿ������
	bool enable_gravity = true;										// �Ƿ���������
	bool is_invulnerable = false;									// �Ƿ��޵�״̬
	StateMachine state_machine;										// ��ɫ״̬��	
	Timer timer_invulnerable_blink;									// �޵�״̬��˸��ʱ��
	Timer timer_invulnerable_status;								// �޵�״̬��ʱ��
	bool is_blink_invisible = false;								// �Ƿ�����˸֡
	CollisionBox* hit_box = nullptr;								// ������ײ��
	CollisionBox* hurt_box = nullptr;								// �ܻ���ײ��
	AnimationGroup* current_animation = nullptr;					// ��ǰ����
	std::unordered_map<std::string, AnimationGroup> animation_pool;	// ��ɫ������

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
