#include "collision_box.h"

CollisionBox::CollisionBox()
{
	enabled = true;
	layer_src = CollisionLayer::NONE;
	layer_dst = CollisionLayer::NONE;
}

CollisionBox::~CollisionBox() = default;

void CollisionBox::set_enabled(bool flag)
{
	enabled = flag;
}

void CollisionBox::set_layer_src(CollisionLayer layer)
{
	layer_src = layer;
}

void CollisionBox::set_layer_dst(CollisionLayer layer)
{
	layer_dst = layer;
}

void CollisionBox::set_on_collide(std::function<void()> on_collide)
{
	this->on_collide = on_collide;
}

void CollisionBox::set_size(const Vec2& size)
{
	this->size = size;
}

void CollisionBox::set_position(const Vec2& position)
{
	this->position = position;
}

const Vec2& CollisionBox::get_size() const
{
	return size;
}