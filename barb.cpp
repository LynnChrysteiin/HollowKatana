#include "barb.h"

#include "character_manager.h"
#include "collision_manager.h"
#include "resource_manager.h"

Barb::Barb()
{
	diff_period = randint(0, 6);

	animation_loose.set_interval(0.15f);
	animation_loose.set_loop(true);
	animation_loose.set_anchor_mode(Animation::AnchorMode::CENTERED);
	animation_loose.add_frame(ResourceManager::instance()->find_atlas("barb_loose"));

	animation_break.set_interval(0.1f);
	animation_break.set_loop(false);
	animation_break.set_anchor_mode(Animation::AnchorMode::CENTERED);
	animation_break.add_frame(ResourceManager::instance()->find_atlas("barb_break"));
	animation_break.set_on_finished([&]() { is_valid = false; });

	collision_box = CollisionManager::instance()->create_collision_box();
	collision_box->set_layer_src(CollisionLayer::ENEMY);
	collision_box->set_layer_dst(CollisionLayer::PLAYER);
	collision_box->set_size({ 20, 20 });
	collision_box->set_on_collide([&]() { on_break(); });

	timer_idle.set_wait_time(static_cast<float>(randint(3, 10)));
	timer_idle.set_one_shot(true);
	timer_idle.set_on_timeout(
		[&]()
		{
			if (stage == Stage::IDLE)
			{
				stage = Stage::AIM;
				base_position = current_position;
			}
		}
	);

	timer_aim.set_wait_time(0.75f);
	timer_aim.set_one_shot(true);
	timer_aim.set_on_timeout(
		[&]()
		{
			if (stage == Stage::AIM)
			{
				stage = Stage::DASH;
				const Vec2& player_position = CharacterManager::instance()->get_player()->get_position();
				velocity = (player_position - current_position).normalize() * SPEED_DASH;
			}
		}
	);
}

Barb::~Barb()
{
	CollisionManager::instance()->destroy_collision_box(collision_box);
}

void Barb::on_update(float delta)
{
	// update timer
	if (stage == Stage::IDLE)
		timer_idle.on_update(delta);
	if (stage == Stage::AIM)
		timer_aim.on_update(delta);

	// update movement
	total_delta_time += delta;
	switch (stage)
	{
	case Stage::IDLE:
		current_position.y = base_position.y + sin(total_delta_time * 2.0f + diff_period) * 30.0f;
		break;
	case Stage::AIM:
		current_position.x = base_position.x + randint(-10, 10);
		break;
	case Stage::DASH:
		current_position += velocity * delta;
		if (current_position.y >= CharacterManager::instance()->get_player()->get_floor_y())
			on_break();
		if (current_position.y <= 0)
			is_valid = false;
		break;
	}
	collision_box->set_position(current_position);

	// update animation
	current_animation = (stage == Stage::BREAK ? &animation_break : &animation_loose);
	current_animation->set_position(current_position);
	current_animation->on_update(delta);
}

void Barb::on_render()
{
	current_animation->on_render();
}

void Barb::set_position(const Vec2& position)
{
	this->base_position = position;
	this->current_position = position;
}

bool Barb::check_valid() const
{
	return is_valid;
}

void Barb::on_break()
{
	if (stage == Stage::BREAK)
		return;
	stage = Stage::BREAK;
	collision_box->set_enabled(false);
	play_audio(_T("barb_break"), false);
}
