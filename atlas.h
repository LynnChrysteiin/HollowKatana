#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <graphics.h>
#include <vector>

class Atlas
{
private:
	std::vector<IMAGE> img_list;

public:
	Atlas();
	~Atlas();

	void load(LPCTSTR path_template, int num);
	void clear();
	int get_size() const;
	IMAGE* get_image(int index);
	void add_image(const IMAGE& img);
};

#endif // !_ATLAS_H_
