#include "collision_manager.h"

#include <graphics.h>

CollisionManager::CollisionManager() = default;
CollisionManager::~CollisionManager() = default;

CollisionManager* CollisionManager::manager = nullptr;

CollisionManager* CollisionManager::instance()
{
	if (!manager)
		manager = new CollisionManager();
	return manager;
}

CollisionBox* CollisionManager::create_collision_box()
{
	CollisionBox* box = new CollisionBox();
	collision_box_list.push_back(box);
	return box;
}

void CollisionManager::destroy_collision_box(CollisionBox* box)
{
	collision_box_list.erase(
		std::remove(collision_box_list.begin(), collision_box_list.end(), box),
		collision_box_list.end()
	);
	delete box;
}

void CollisionManager::process_collision()
{
	for (CollisionBox* box_src : collision_box_list)
	{
		if (!box_src->enabled || box_src->layer_dst == CollisionLayer::NONE)
			continue;

		for (CollisionBox* box_dst : collision_box_list)
		{
			if (!box_dst->enabled || box_src == box_dst || box_src->layer_dst != box_dst->layer_src)
				continue;

			bool is_collide_x = (
				max(box_src->position.x + box_src->size.x / 2, box_dst->position.x + box_dst->size.x / 2) -
				min(box_src->position.x - box_src->size.x / 2, box_dst->position.x - box_dst->size.x / 2)
				) <= (box_src->size.x + box_dst->size.x);
			bool is_collide_y = (
				max(box_src->position.y + box_src->size.y / 2, box_dst->position.y + box_dst->size.y / 2) -
				min(box_src->position.y - box_src->size.y / 2, box_dst->position.y - box_dst->size.y / 2)
				) <= (box_src->size.y + box_dst->size.y);

			if (is_collide_x && is_collide_y && box_dst->on_collide)
				box_dst->on_collide();
		}
	}
}

void CollisionManager::on_debug_render()
{
	for (CollisionBox* box : collision_box_list)
	{
		setlinecolor(box->enabled ? RGB(255, 195, 195) : RGB(115, 115, 175));
		rectangle(
			static_cast<int>(box->position.x - box->size.x / 2),
			static_cast<int>(box->position.y - box->size.y / 2),
			static_cast<int>(box->position.x + box->size.x / 2),
			static_cast<int>(box->position.y + box->size.y / 2)
		);
	}
	setbkmode(TRANSPARENT);
	outtextxy(20, getheight() - 40, _T("调试模式已开启，按下“F1”关闭。"));
}
