#include "TextBox.h"


TextBox::TextBox(uint32_t width) : Control(width, DEFAULT_HEIGHT, true, true), _cursorPosition(0)
{
}

TextBox::~TextBox()
{
}

void TextBox::setText(std::string value)
{
	if (value.size() <= getWidth())
	{
		_value = value;
		_cursorPosition = value.length();
	}
	else
		throw StringWiderThenWidthOfControl(); // if string is wider then control throw exception.
}

void TextBox::setText(std::wstring value)
{
	std::string str(value.begin(), value.end());
	setText(str);
}

void TextBox::draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
	if (z == getLayer())
	{
		g.setBackground(getBackground());
		g.setForeground(getForeground());
		g.write(getCoords().X, getCoords().Y, getText());
		if (this == Control::getFocus()) // if control is focused, show cursor.
		{
			g.setCursorVisibility(true);
			g.moveTo(getCoords().X, getCoords().Y);
		}
		drawBorder(g, x, y, z);
	}
}

void TextBox::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
	if (isLeft)
	{
		if (x - getLeft() < getWidth())
		{
			Control::setFocus(*this);
			_cursorPosition = ((x - getLeft()) < _value.length()) ? (x - getLeft()) : _value.length();
		}
	}
}

void TextBox::keyDown(uint32_t keyCode, char character)
{
	switch (keyCode)
	{
	case VK_BACK:
		if (!_value.empty())
			if (_cursorPosition > 0)
				_value.erase(--_cursorPosition, 1);
		break;
	case VK_DELETE:
		if (_cursorPosition != _value.length())
			if (_cursorPosition == 0)
				_value.erase(_cursorPosition, 1);
			else
				_value.erase(_cursorPosition + 1, 1);
		break;
	case VK_NUMPAD4:
	case VK_LEFT:
		if (_cursorPosition > 0)
			_cursorPosition--;
		break;
	case VK_NUMPAD6:
	case VK_RIGHT:
		if (!_value.empty())
			if (_cursorPosition < getWidth() && _cursorPosition <= _value.length() - 1)
				_cursorPosition++;
		break;
	case VK_RETURN:
	case VK_UP:
	case VK_DOWN:
	case VK_SHIFT:
	case VK_CONTROL:
		break;
	default:
		std::string t;
		t = character;
		if (_value.length() < getWidth())
			_value.insert(_cursorPosition++, t);
		break;
	}
}

std::string TextBox::getText(void) const
{
	return _value;
}

uint32_t TextBox::getCursorPosition(void) const
{
	return _cursorPosition;
}

void TextBox::setCursorToEnd(void)
{
	_cursorPosition = _value.length();
}
