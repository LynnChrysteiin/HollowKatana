#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "atlas.h"
#include "timer.h"
#include "util.h"
#include "vec2.h"

#include <vector>
#include <functional>

class Animation
{
private:
	struct Frame
	{
		IMAGE* image = nullptr;
		Rect rect_src;

		Frame() = default;
		Frame(IMAGE* img, const Rect& rect_src) : image(img), rect_src(rect_src) {}
		~Frame() = default;
	};

public:
	enum class AnchorMode
	{
		CENTERED,
		BOTTOM_CENTERED,
	};

private:
	Timer timer;
	Vec2 position;
	bool is_loop = true;
	size_t index_frame = 0;
	std::vector<Frame> frame_list;
	std::function<void()> on_finished;
	AnchorMode anchor_mode = AnchorMode::CENTERED;

public:
	Animation();
	~Animation();

	void reset();
	void set_anchor_mode(AnchorMode mode);
	void set_position(const Vec2& pos);
	void set_loop(bool flag);
	void set_interval(float interval);
	void set_on_finished(const std::function<void()> on_finished);
	void add_frame(IMAGE* image, int num_h);
	void add_frame(Atlas* atlas);
	void on_update(float delta);
	void on_render();
};

#endif // !_ANIMATION_H_
