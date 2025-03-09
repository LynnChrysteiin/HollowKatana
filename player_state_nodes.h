#ifndef _PLAYER_STATE_NODES_H_
#define _PLAYER_STATE_NODES_H_

#include "state_node.h"
#include "timer.h"

class PlayerAttackState : public StateNode
{
private:
	Timer timer;

private:
	void update_hit_box_position();

public:
	PlayerAttackState();
	~PlayerAttackState();

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

class PlayerDeadState : public StateNode
{
private:
	Timer timer;

public:
	PlayerDeadState();
	~PlayerDeadState();

	void on_enter() override;
	void on_update(float delta) override;
};

class PlayerIdleState : public StateNode
{
public:
	PlayerIdleState();
	~PlayerIdleState();

	void on_enter() override;
	void on_update(float delta) override;
};

class PlayerFallState : public StateNode
{
public:
	PlayerFallState();
	~PlayerFallState();

	void on_enter() override;
	void on_update(float delta) override;
};

class PlayerJumpState : public StateNode
{
public:
	PlayerJumpState();
	~PlayerJumpState();

	void on_enter() override;
	void on_update(float delta) override;
};

class PlayerRollState : public StateNode
{
private:
	Timer timer;

public:
	PlayerRollState();
	~PlayerRollState();

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

class PlayerRunState : public StateNode
{
public:
	PlayerRunState();
	~PlayerRunState();

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

#endif // !_PLAYER_STATE_NODES_H_