#include "Panel.h"


Panel::Panel(const uint32_t& height, const uint32_t& width) : Control(width, height, true, true)
{
}


Panel::~Panel()
{
}

void Panel::draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
	for (auto i : _controls)
	{
		i->draw(g, x, y, z);
	}
	drawBorder(g, x, y, z);
}

void Panel::addControl(IControl& control, uint32_t x, uint32_t y)
{
	control.setCoords(x, y);
	_controls.push_back(&control);
}

void Panel::getAllControls(std::vector<Control*>& fill)
{
	for (auto i : _controls)
		fill.push_back(dynamic_cast<Control*>(i));
}

void Panel::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
	auto t = _controls;
	std::sort(t.begin(), t.end(), Control::less_than_key()); // sort by layer, make sure clicked control is top.
	if (isLeft)
	{
		for (auto it : t)
		{
			Control* ptr = dynamic_cast<Control*>(it);
			if (!ptr->isClickAble()) continue;
			if (isInside(x, y, ptr->getLeft(), ptr->getTop(), ptr->getWidth(), ptr->getHeight()))
			{
				if (ptr->getHidden()) continue;
				ptr->mousePressed(x, y, isLeft);
				return;
			}
			else
			{
				ptr->closeBox();
			}
		}
	}
}

void Panel::mouseHover(uint32_t x, uint32_t y, bool isLeft)
{
	for (auto it : _controls)
	{
		auto* ptr = dynamic_cast<Control*>(it);
		if (isInside(x, y, ptr->getLeft(), ptr->getTop(), ptr->getWidth(), ptr->getHeight()))
		{
			ptr->mouseHover(x, y, isLeft);
		}
	}
}
