#include "character_manager.h"

#include "bullet_time_manager.h"
#include "enemy.h"
#include "player.h"

CharacterManager* CharacterManager::manager = nullptr;

CharacterManager::CharacterManager()
{
	player = new Player();
	enemy = new Enemy();
}

CharacterManager::~CharacterManager()
{
	if (player)
		delete player;
	if (enemy)
		delete enemy;
}

CharacterManager* CharacterManager::instance()
{
	if (manager == nullptr)
		manager = new CharacterManager();
	return manager;
}

Character* CharacterManager::get_player()
{
	return player;
}

Character* CharacterManager::get_enemy()
{
	return enemy;
}

void CharacterManager::on_input(const ExMessage& msg)
{
	player->on_input(msg);
}

void CharacterManager::on_update(float delta)
{
	enemy->on_update(delta);
	player->on_update(delta);
}

void CharacterManager::on_render()
{
	enemy->on_render();
	BulletTimeManager::instance()->post_process();
	player->on_render();
}
