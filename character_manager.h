#ifndef _CHARACTER_MANAGER_H_
#define _CHARACTER_MANAGER_H_

#include "character.h"

class CharacterManager
{
private:
	static CharacterManager* manager;
	Character* player = nullptr;
	Character* enemy = nullptr;

private:
	CharacterManager();
	~CharacterManager();

public:
	static CharacterManager* instance();

	Character* get_player();
	Character* get_enemy();
	
	void on_input(const ExMessage& msg);
	void on_update(float delta);
	void on_render();
};

#endif // !_CHARACTER_MANAGER_H_