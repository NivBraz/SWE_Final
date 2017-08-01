#include "CheckList.h"


CheckList::CheckList(uint32_t height, uint32_t width, std::vector<std::string> entries) : AbstractBox(height, width, entries, CHECKLIST_TEXT), _selected(0)
{
}

CheckList::~CheckList()
{
}

std::vector<size_t> CheckList::getSelectedIndices() const
{
	return _selected;
}

void CheckList::selectIndex(size_t index)
{
	if (index > _entries.size())
		throw IndexOutOfBounds(); // Index is out of bounds. throw exception.
	if (std::find(_selected.begin(), _selected.end(), index) != _selected.end())
		return; // index already checked.
	_selected.push_back(index);
	std::sort(_selected.begin(), _selected.end());
	Control* ptr = _entries[index];
	MousePressed(*ptr, 0, 0, 0);
}

void CheckList::deselectIndex(size_t index)
{
	if (index > _entries.size())
		throw IndexOutOfBounds(); // Index is out of bounds. throw exception.
	auto it = std::find(_selected.begin(), _selected.end(), index);
	if (it == _selected.end())
		return; // index is uncheckde.
	_selected.erase(it);
	Control* ptr = _entries[index];
	MousePressed(*ptr, 0, 0, 0);
}

void CheckList::MousePressed(Control& control, int x, int y, bool isLeft, Control* msCb)
{
	auto ptr = dynamic_cast<Button*>(&control);
	auto t = ptr->getText();
	if (t[1] != BOXCHECK) // not checked?
	{
		t[1] = BOXCHECK; // check it!
		ptr->setText(t);
	}
	else
	{
		t[1] = BOXUNCHECK; // uncheck.
		ptr->setText(t);
	}
}

void CheckList::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
	if (getHidden()) return;
	uint32_t h = this->getCoords().Y;
	uint32_t count = 0;
	for (auto it : _entries)
	{
		if (isInside(x, y, it->getLeft(), it->getTop(), it->getWidth(), it->getHeight()))
		{
			it->mousePressed(x, y, isLeft);
			_current = count;
			Control::setFocus(*this);
			return;
		}
		count++;
	}
}

void CheckList::keyDown(uint32_t keyCode, char character)
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
		selectOrDeselect(_current);
		break;
	case VK_TAB:
		if (_current < _entries.size() - 1)
			_current++;
		break;
	default:
		break;
	}
}

void CheckList::setBackground(Color color)
{
	for (auto it : _entries)
	{
		it->setBackground(color);
	}
	Control::setBackground(color);
}

void CheckList::setForeground(Color color)
{
	for (auto it : _entries)
	{
		it->setForeground(color);
	}
	Control::setForeground(color);
}

void CheckList::selectOrDeselect(uint32_t index)
{
	if (std::find(_selected.begin(), _selected.end(), index) != _selected.end())
		deselectIndex(index); // if found in selected vector, deselect.
	else
		selectIndex(index); // else select
}
