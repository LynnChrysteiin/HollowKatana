#ifndef _UTIL_H_
#define _UTIL_H_

#include <graphics.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

struct Rect
{
	int x, y, w, h;
};

inline void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(
		GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0,
		rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(),
		blend_func
	);
}

inline void sketch_frame(IMAGE* src, IMAGE* dst, COLORREF color_ref = RGB(255, 255, 255))
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx = y * w + x;
			dst_buf[idx] = BGR(color_ref) | (src_buf[idx] & 0xFF000000);
		}
	}
}

inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	mciSendString(str_cmd, nullptr, 0, nullptr);
}

inline void play_audio(LPCTSTR id, bool is_loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, is_loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, nullptr, 0, nullptr);
}

inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	mciSendString(str_cmd, nullptr, 0, nullptr);
}

inline int randint(int min, int max)
{
	return min + rand() % (max - min + 1);
}

#endif // !_UTIL_H_
