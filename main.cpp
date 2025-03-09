#include "bullet_time_manager.h"
#include "character_manager.h"
#include "collision_manager.h"
#include "resource_manager.h"
#include "util.h"

#include <chrono>
#include <graphics.h>
#include <thread>

bool is_debug_rendering = false;

static void render_background()
{
	static IMAGE* img_background = ResourceManager::instance()->find_image("background");
	static Rect rect_dst =
	{
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	putimage_ex(img_background, &rect_dst);
}

static void rander_remain_hp()
{
	static IMAGE* img_ui_heart = ResourceManager::instance()->find_image("ui_heart");
	Rect rect_dst_player = { 0, 10, img_ui_heart->getwidth(), img_ui_heart->getheight() };
	Rect rect_dst_enemy = { 0, 10, img_ui_heart->getwidth(), img_ui_heart->getheight() };
	for (int i = 0; i < CharacterManager::instance()->get_player()->get_hp(); i++)
	{
		rect_dst_player.x = 10 + i * 40;
		putimage_ex(img_ui_heart, &rect_dst_player);
	}
	for (int i = 0; i < CharacterManager::instance()->get_enemy()->get_hp(); i++)
	{
		rect_dst_enemy.x = getwidth() - 10 - (i + 1) * 40;
		putimage_ex(img_ui_heart, &rect_dst_enemy);
	}
}

int main(int argc, char** argv)
{
	using namespace std::chrono;

	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("Hollow Katana"));

	try
	{
		ResourceManager::instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("Failed to load image: %s"), id);
		MessageBox(hwnd, err_msg, _T("Failed to load resources"), MB_OK | MB_ICONERROR);
		return -1;
	}

	play_audio(_T("bgm"), true);

	const int FPS = 60;
	const nanoseconds FRAME_DURATION(1000000000 / FPS);
	steady_clock::time_point last_tick = steady_clock::now();

	ExMessage msg;
	bool is_quit = false;

	BeginBatchDraw();

	while (!is_quit)
	{
		while (peekmessage(&msg))
		{
			// handle message
			CharacterManager::instance()->on_input(msg);
			// !handle message
		}

		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		// update
		float scaled_time = BulletTimeManager::instance()->on_update(delta.count());
		CharacterManager::instance()->on_update(scaled_time);
		CollisionManager::instance()->process_collision();
		// !update

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		// render
		render_background();
		CharacterManager::instance()->on_render();
		if (is_debug_rendering)
			CollisionManager::instance()->on_debug_render();
		rander_remain_hp();
		// !render

		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = FRAME_DURATION - duration_cast<nanoseconds>(steady_clock::now() - frame_start);
		if (sleep_duration > nanoseconds::zero())
			std::this_thread::sleep_for(sleep_duration);
	}

	EndBatchDraw();
	closegraph();

	return 0;
}
