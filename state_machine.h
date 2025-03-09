#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "state_node.h"

#include <graphics.h>
#include <string>
#include <unordered_map>

class StateMachine
{
private:
	bool need_init = true;
	StateNode* current_state = nullptr;
	std::unordered_map<std::string, StateNode*> state_pool;

public:
	StateMachine();
	~StateMachine();

	void on_update(float delta);
	void set_entry(const std::string& id);
	void switch_to(const std::string& id);
	void register_state(const std::string& id, StateNode* node);
};

#endif // !_STATE_MACHINE_H_
