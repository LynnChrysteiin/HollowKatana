#include "animation.h"

Animation::Animation()
{
	timer.set_one_shot(false);
	timer.set_on_timeout(
		[&]()
		{
			index_frame++;
			if (index_frame >= frame_list.size())
			{
				index_frame = is_loop ? 0 : frame_list.size() - 1;
				if (!is_loop && on_finished)
				{
					on_finished();
				}
			}
		}
	);
}

Animation::~Animation() = default;

void Animation::reset()
{
	timer.restart();
	index_frame = 0;
}

void Animation::set_anchor_mode(AnchorMode mode)
{
	anchor_mode = mode;
}

void Animation::set_position(const Vec2& pos)
{
	position = pos;
}

void Animation::set_loop(bool flag)
{
	is_loop = flag;
}

void Animation::set_interval(float interval)
{
	timer.set_wait_time(interval);
}

void Animation::set_on_finished(const std::function<void()> on_finished)
{
	this->on_finished = on_finished;
}

void Animation::add_frame(IMAGE* image, int num_h)
{
	int width = image->getwidth();
	int height = image->getheight();
	int width_frame = width / num_h;

	for (int i = 0; i < num_h; i++)
	{
		Rect rect_src{};
		rect_src.x = i * width_frame, rect_src.y = 0;
		rect_src.w = width_frame, rect_src.h = height;

		frame_list.emplace_back(image, rect_src);
	}
}

void Animation::add_frame(Atlas* atlas)
{
	for (int i = 0; i < atlas->get_size(); i++)
	{
		IMAGE* image = atlas->get_image(i);
		int width = image->getwidth();
		int height = image->getheight();

		Rect rect_src{};
		rect_src.x = 0, rect_src.y = 0;
		rect_src.w = width, rect_src.h = height;

		frame_list.emplace_back(image, rect_src);
	}
}

void Animation::on_update(float delta)
{
	timer.on_update(delta);
}

void Animation::on_render()
{
	const Frame& frame = frame_list[index_frame];

	Rect rect_dst{};
	rect_dst.x = static_cast<int>(position.x) - frame.rect_src.w / 2;
	rect_dst.y = (anchor_mode == AnchorMode::CENTERED) ?
		static_cast<int>(position.y) - frame.rect_src.h / 2 :
		static_cast<int>(position.y) - frame.rect_src.h;
	rect_dst.w = frame.rect_src.w, rect_dst.h = frame.rect_src.h;

	putimage_ex(frame.image, &rect_dst, &frame.rect_src);
}
