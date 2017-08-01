#include "Button.h"

Button::Button(uint32_t width) : Control(width, DEFAULT_HEIGHT, false, true)
{
}

Button::~Button()
{
}

void Button::setText(std::string value)
{
	uint32_t w = getWidth();
	if (value.length() <= w)
	{
		if (w > _value.size())
			value.insert(value.end(), w - value.size(), TEXT_PADDING); // Pad string to match width.
		_value = value;
	}
	else
		throw StringWiderThenWidthOfControl(); // if string is wider then control throw exception.
}

std::string Button::getText(void) const
{
	return _value;
}


void Button::addListener(MouseListener& listener)
{
	ml = &listener;
}

void Button::draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
	if (z == getLayer())
	{
		g.setBackground(getBackground());
		g.setForeground(getForeground());
		g.write(getCoords().X, getCoords().Y, _value);
		drawBorder(g, x, y, z);
	}
}

void Button::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
	ml->MousePressed(*this, x, y, isLeft);
}
