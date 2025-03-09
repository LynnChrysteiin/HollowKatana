#include "player_state_nodes.h"

#include "character_manager.h"
#include "player.h"
#include "util.h"

PlayerAttackState::PlayerAttackState()
{
	timer.set_wait_time(0.3f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());
			player->set_attacking(false);
		}
	);
}

PlayerAttackState::~PlayerAttackState() = default;

void PlayerAttackState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("attack");

	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());
	player->get_hit_box()->set_enabled(true);
	player->set_attacking(true);
	update_hit_box_position();
	player->on_attack();
	timer.restart();

	switch (randint(1, 3))
	{
	case 1:
		play_audio(_T("player_attack_1"), false);
		break;
	case 2:
		play_audio(_T("player_attack_2"), false);
		break;
	case 3:
		play_audio(_T("player_attack_3"), false);
		break;
	}
}

void PlayerAttackState::on_update(float delta)
{
	timer.on_update(delta);
	update_hit_box_position();

	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());

	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (!player->get_attacking())
	{
		if (player->get_velocity().y > 0)
			player->switch_state("fall");
		else if (player->get_move_axis() == 0)
			player->switch_state("idle");
		else if (player->is_on_floor() && player->get_move_axis() != 0)
			player->switch_state("run");
	}
}

void PlayerAttackState::on_exit()
{
	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());
	player->get_hit_box()->set_enabled(false);
	player->set_attacking(false);
}

void PlayerAttackState::update_hit_box_position()
{
	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());
	Vec2 pos_center = player->get_logic_center();
	CollisionBox* hit_box = player->get_hit_box();
	const Vec2& size_hit_box = hit_box->get_size();
	Vec2 pos_hit_box;

	switch (player->get_attack_dir())
	{
	case Player::AttackDir::UP:
		pos_hit_box = { pos_center.x, pos_center.y - size_hit_box.y / 2 };
		break;
	case Player::AttackDir::DOWN:
		pos_hit_box = { pos_center.x, pos_center.y + size_hit_box.y / 2 };
		break;
	case Player::AttackDir::LEFT:
		pos_hit_box = { pos_center.x - size_hit_box.x / 2, pos_center.y };
		break;
	case Player::AttackDir::RIGHT:
		pos_hit_box = { pos_center.x + size_hit_box.x / 2, pos_center.y };
		break;
	default:
		break;
	}
	hit_box->set_position(pos_hit_box);
}

PlayerDeadState::PlayerDeadState()
{
	timer.set_wait_time(2.0f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			MessageBox(GetHWnd(), _T("不对......\n这样不行。"), _T("挑战失败！"), MB_OK);
			exit(0);
		}
	);
}

PlayerDeadState::~PlayerDeadState() = default;

void PlayerDeadState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("dead");
	play_audio(_T("player_dead"), false);
}

void PlayerDeadState::on_update(float delta)
{
	timer.on_update(delta);
}

PlayerFallState::PlayerFallState() = default;
PlayerFallState::~PlayerFallState() = default;

void PlayerFallState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("fall");
}

void PlayerFallState::on_update(float delta)
{
	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());
	
	if(player->get_hp() <= 0)
		player->switch_state("dead");
	else if (player->is_on_floor())
	{
		player->switch_state("idle");
		player->on_land();
		play_audio(_T("player_land"), false);
	}
	else if (player->can_attack())
		player->switch_state("attack");
}

PlayerIdleState::PlayerIdleState() = default;
PlayerIdleState::~PlayerIdleState() = default;

void PlayerIdleState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("idle");
}

void PlayerIdleState::on_update(float delta)
{
	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());

	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (player->can_attack())
		player->switch_state("attack");
	else if (player->get_velocity().y > 0)
		player->switch_state("fall");
	else if (player->can_jump())
		player->switch_state("jump");
	else if (player->can_roll())
		player->switch_state("roll");
	else if (player->is_on_floor() && player->get_move_axis() != 0)
		player->switch_state("run");
}

PlayerJumpState::PlayerJumpState() = default;
PlayerJumpState::~PlayerJumpState() = default;

void PlayerJumpState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("jump");

	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());
	player->on_jump();

	play_audio(_T("player_jump"), false);
}

void PlayerJumpState::on_update(float delta)
{
	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());

	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (player->get_velocity().y > 0)
		player->switch_state("fall");
	else if (player->can_attack())
		player->switch_state("attack");
}

PlayerRollState::PlayerRollState()
{
	timer.set_wait_time(0.35f);
	timer.set_one_shot(true);
	timer.set_on_timeout([&]()
		{
			Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());
			player->set_rolling(false);
		}
	);
}

PlayerRollState::~PlayerRollState() = default;

void PlayerRollState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("roll");

	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());
	player->get_hurt_box()->set_enabled(false);
	player->set_rolling(true);
	player->on_roll();
	timer.restart();

	play_audio(_T("player_roll"), false);
}

void PlayerRollState::on_update(float delta)
{
	timer.on_update(delta);

	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());

	if (!player->get_rolling())
	{
		if (player->get_move_axis() != 0)
			player->switch_state("run");
		else if (player->can_jump())
			player->switch_state("jump");
		else
			player->switch_state("idle");
	}
}

void PlayerRollState::on_exit()
{
	CharacterManager::instance()->get_player()->get_hurt_box()->set_enabled(true);
}

PlayerRunState::PlayerRunState() = default;
PlayerRunState::~PlayerRunState() = default;

void PlayerRunState::on_enter()
{
	CharacterManager::instance()->get_player()->set_animation("run");
	play_audio(_T("player_run"), true);
}

void PlayerRunState::on_update(float delta)
{
	Player* player = static_cast<Player*>(CharacterManager::instance()->get_player());

	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (player->can_attack())
		player->switch_state("attack");
	else if (player->get_move_axis() == 0)
		player->switch_state("idle");
	else if (player->can_jump())
		player->switch_state("jump");
	else if (player->can_roll())
		player->switch_state("roll");
}

void PlayerRunState::on_exit()
{
	stop_audio(_T("player_run"));
}