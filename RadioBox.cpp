#include "RadioBox.h"


void RadioBox::ClearAstrix()
{
	auto it = _entries.begin();
	for (uint32_t i = 0; i < _entries.size(); ++i , ++it)
	{
		if (i == _selected) continue;
		auto t = (*it)->getText();
		if (t[0] == BOXCHECK) // checked?
			t[0] = BOXUNCHECK; // uncheck box.
		(*it)->setText(t);
	}
}

RadioBox::RadioBox(uint32_t height, uint32_t width, std::vector<std::string> entries) : AbstractBox(height, width, entries, RADIOBOX_TEXT), _selected(0)
{
}

RadioBox::~RadioBox()
{
}


size_t RadioBox::getSelectedIndex() const
{
	return _selected;
}

void RadioBox::setSelectedIndex(size_t index)
{
	if (index > _entries.size())
		throw IndexOutOfBounds(); // Index is out of bounds. throw exception.
	_selected = index;
	Control* ptr = _entries[_selected];
	MousePressed(*ptr, 0, 0, 0);
}

void RadioBox::MousePressed(Control& control, int x, int y, bool isLeft, Control* msCb)
{
	auto* ptr = dynamic_cast<Button*>(&control);
	auto t = ptr->getText();
	if (t[0] != BOXCHECK)
	{
		t[0] = BOXCHECK;
		ptr->setText(t);
	}
}


void RadioBox::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
	if (getHidden()) return;
	uint32_t h = this->getCoords().Y;
	uint32_t count = 0;
	for (auto it : _entries)
	{
		if (isInside(x, y, it->getLeft(), it->getTop(), it->getWidth(), it->getHeight()))
		{
			it->mousePressed(x, y, isLeft);
			if (_selected != count)
			{
				_selected = count;
				_current = _selected;
				ClearAstrix();
			}
			Control::setFocus(*this);
			return;
		}
		count++;
	}
}

void RadioBox::keyDown(uint32_t keyCode, char character)
{
	if (getHidden()) return;
	switch (keyCode)
	{
	case VK_NUMPAD8:
	case VK_UP:
		if (_current > 0)
		{
			_current--;
		}
		break;
	case VK_NUMPAD2:
	case VK_DOWN:
		if (_current < _entries.size() - 1)
			_current++;
		break;
	case VK_SPACE:
	case VK_RETURN:
		_selected = _current;
		setSelectedIndex(_selected);
		ClearAstrix();
		break;
	case VK_TAB:
		if (_current < _entries.size() - 1)
			_current++;
		break;
	default:
		break;
	}
}

void RadioBox::setBackground(Color color)
{
	for (auto it : _entries)
	{
		it->setBackground(color);
	}
	Control::setBackground(color);
}

void RadioBox::setForeground(Color color)
{
	for (auto it : _entries)
	{
		it->setForeground(color);
	}
	Control::setForeground(color);
}
