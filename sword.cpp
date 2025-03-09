#include "sword.h"

#include "collision_manager.h"
#include "resource_manager.h"

Sword::Sword() = default;

Sword::Sword(const Vec2& position, bool move_left)
{
	animation.set_interval(0.1f);
	animation.set_loop(true);
	animation.set_anchor_mode(Animation::AnchorMode::CENTERED);
	animation.add_frame(ResourceManager::instance()->find_atlas(move_left ? "sword_left" : "sword_right"));

	collision_box = CollisionManager::instance()->create_collision_box();
	collision_box->set_layer_src(CollisionLayer::NONE);
	collision_box->set_layer_dst(CollisionLayer::PLAYER);
	collision_box->set_size({ 195, 10 });

	this->position = position;
	this->velocity = { move_left ? -SPEED_MOVE : SPEED_MOVE, 0 };
}

Sword::~Sword()
{
	CollisionManager::instance()->destroy_collision_box(collision_box);
}

void Sword::on_update(float delta)
{
	position += velocity * delta;
	animation.set_position(position);
	collision_box->set_position(position);

	animation.on_update(delta);

	if (position.x <= -200 || position.x >= getwidth() + 200)
		is_valid = false;
}

void Sword::on_render()
{
	animation.on_render();
}

bool Sword::check_valid() const
{
	return is_valid;
}