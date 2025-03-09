#ifndef _ENEMY_STATE_NODES_H_
#define _ENEMY_STATE_NODES_H_

#include "state_node.h"
#include "timer.h"

class EnemyAimState : public StateNode
{
private:
	Timer timer;

public:
	EnemyAimState();
	~EnemyAimState() = default;

	void on_enter() override;
	void on_update(float delta) override;
};

class EnemyDashInAirState : public StateNode
{
private:
	const float SPEED_DASH = 1500.0f;

public:
	EnemyDashInAirState() = default;
	~EnemyDashInAirState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

class EnemyDashOnFloorState : public StateNode
{
private:
	const float SPEED_DASH = 1000.0f;

private:
	Timer timer;

public:
	EnemyDashOnFloorState();
	~EnemyDashOnFloorState() = default;

	void on_enter() override;
	void on_update(float delta) override;
};

class EnemyDeadState : public StateNode
{
public:
	EnemyDeadState() = default;
	~EnemyDeadState() = default;

	void on_enter() override;
};

class EnemyFallState : public StateNode
{
public:
	EnemyFallState() = default;
	~EnemyFallState() = default;

	void on_enter() override;
	void on_update(float delta) override;
};

class EnemyIdleState : public StateNode
{
private:
	Timer timer;

public:
	EnemyIdleState();
	~EnemyIdleState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

class EnemyJumpState : public StateNode
{
private:
	const float SPEED_JUMP = 1000.0f;

public:
	EnemyJumpState() = default;
	~EnemyJumpState() = default;

	void on_enter() override;
	void on_update(float delta) override;
};

class EnemyRunState : public StateNode
{
private:
	const float MIN_DIS = 350.f;
	const float SPEED_RUN = 500.0f;

public:
	EnemyRunState() = default;
	~EnemyRunState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};

class EnemySquatState : public StateNode
{
private:
	Timer timer;

public:
	EnemySquatState();
	~EnemySquatState() = default;

	void on_enter() override;
	void on_update(float delta) override;
};

class EnemyThrowBarbState : public StateNode
{
private:
	Timer timer;

public:
	EnemyThrowBarbState();
	~EnemyThrowBarbState() = default;

	void on_enter() override;
	void on_update(float delta) override;
};

class EnemyThrowSilkState : public StateNode
{
private:
	Timer timer;

public:
	EnemyThrowSilkState();
	~EnemyThrowSilkState() = default;

	void on_enter() override;
	void on_update(float delta) override;
};

class EnemyThrowSwordState : public StateNode
{
private:
	Timer timer_throw;
	Timer timer_switch;

public:
	EnemyThrowSwordState();
	~EnemyThrowSwordState() = default;

	void on_enter() override;
	void on_update(float delta) override;
};

#endif // !_ENEMY_STATE_NODES_H_