#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
private:
	float pass_time = 0.0f;
	float wait_time = 0.0f;
	bool paused = false;
	bool shotted = false;
	bool one_shot = false;
	std::function<void()> on_timeout;

public:
	Timer();
	~Timer();

	void restart();
	void set_wait_time(float value);
	void set_one_shot(bool flag);
	void set_on_timeout(std::function<void()> on_timeout);
	void pause();
	void resume();
	void on_update(float delta);
};

#endif // !_TIMER_H_
