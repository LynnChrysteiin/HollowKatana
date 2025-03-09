#ifndef _BULLET_TIME_MANAGER_H_
#define _BULLET_TIME_MANAGER_H_

class BulletTimeManager
{
public:
	enum class Status
	{
		ENTERING,
		EXITING,
	};

public:
	static BulletTimeManager* instance();

	void post_process();
	void set_status(Status status);
	float on_update(float delta);

private:
	static BulletTimeManager* manager;
	
	float progress = 0;
	Status status = Status::EXITING;
	const float SPEED_PROGRESS = 2.0f;
	const float DST_DELTA_FACTOR = 0.35f;
	const float DST_COLOR_FACTOR = 0.35f;

private:
	BulletTimeManager();
	~BulletTimeManager();

	float lerp(float start, float end, float t);
};

#endif // _BULLET_TIME_MANAGER_H_