#ifndef _COLLISION_BOX_H_
#define _COLLISION_BOX_H_

#include "vec2.h"
#include "collision_layer.h"

#include <functional>

class CollisionManager;

class CollisionBox
{
	friend class CollisionManager;

private:
	Vec2 size;
	Vec2 position;
	bool enabled;
	std::function<void()> on_collide;
	CollisionLayer layer_src;
	CollisionLayer layer_dst;

private:
	CollisionBox();
	~CollisionBox();

public:
	void set_enabled(bool flag);
	void set_layer_src(CollisionLayer layer);
	void set_layer_dst(CollisionLayer layer);
	void set_on_collide(std::function<void()> on_collide);
	void set_size(const Vec2& size);
	void set_position(const Vec2& position);
	const Vec2& get_size() const;
};

#endif // !_COLLISION_BOX_H_
