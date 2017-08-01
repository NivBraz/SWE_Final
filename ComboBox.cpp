#include "ComboBox.h"

ComboBox::ComboBox(uint32_t width, std::vector<std::string> entries) : Control(width, DEFAULT_HEIGHT * entries.size(), true, true), _selected(0), _current(0), _isOpen(false), _redrawFlag(false)
{
	std::sort(entries.begin(), entries.end()); // sort by name.
	for (uint32_t i = 0; i < entries.size(); ++i)
		_entries.push_back(new Button(width));
	_selectedControl = _entries[0];
	auto _it = _entries.begin();

	for (auto it : entries)
	{
		(*_it)->setText(it);

		(*_it)->addListener(*this);
		++_it;
	}
}

ComboBox::~ComboBox()
{
	Button* ptr;
	for (auto it : _entries)
	{
		ptr = it;
		delete ptr;
	}
}

size_t ComboBox::getSelectedIndex() const
{
	return _selected;
}

void ComboBox::setSelectedIndex(size_t index)
{
	if (index >= _entries.size())
		throw IndexOutOfBounds(); // Index is out of bounds. throw exception.
	_selected = index;
	_selectedControl = _entries[index];
}

void ComboBox::draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
	if (getHidden()) return;
	if (z <= getLayer())
	{
		if (_isOpen) // if ComboBox is open, draw all entries.
		{
			uint32_t h = this->getCoords().Y;
			uint32_t counter = 0;
			for (auto it : _entries)
			{
				if (this != Control::getFocus()) //if we lost focus, repaint control black.
				{
					if (it->getBackground() == Color::Blue) it->setBackground(getBackground());
					it->draw(g, this->getCoords().X, h, z);
					h += DEFAULT_HEIGHT;
				}
				else
				{
					if (counter == _current)
					{
						it->setBackground(Color::Blue); // control is focused. paint blue.
					}
					else
					{
						if (it->getBackground() == Color::Blue) it->setBackground(getBackground()); // remove blue paint from unfocused control.
					}
					it->draw(g, this->getCoords().X, h, z);
					h += DEFAULT_HEIGHT;
					counter++;
				}
			}
			//	g.moveCursor(_selectedControl->GetCoords());
		}
		else // ComboBox is closed. draw only selected entry.
		{
			if (Control::getFocus() == this)
				_selectedControl->setBackground(Color::Blue);
			else
				_selectedControl->setBackground(getBackground());
			g.setBackground(_selectedControl->getBackground());
			g.setForeground(_selectedControl->getForeground());
			g.write(getCoords().X, getCoords().Y, _selectedControl->getText());
		}
		drawBorder(g, x, y, z);
	}
}

void ComboBox::MousePressed(Control& control, int x, int y, bool isLeft, Control* msCb)
{
	if (_isOpen)
	{
		auto* ptr = dynamic_cast<Button*>(&control);
		_selectedControl = ptr;
		_selected = std::find(_entries.begin(), _entries.end(), ptr) - _entries.begin();
		_isOpen = false;
	}
	else
	{
		openBox();
	}
}

void ComboBox::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
	if (getHidden()) return;
	uint32_t count = 0;
	for (auto it : _entries)
	{
		if (isInside(x, y, it->getLeft(), it->getTop(), it->getWidth(), it->getHeight()))
		{
			it->mousePressed(x, y, isLeft);
			_selected = count;

			Control::setFocus(*this);
			return;
		}
		count++;
	}
}

void ComboBox::mouseHover(uint32_t x, uint32_t y, bool isLeft)
{
	uint32_t count = 0;
	if (getHidden()) return;
	if (!_isOpen) return;
	for (auto it : _entries)
	{
		if (isInside(x, y, it->getLeft(), it->getTop(), it->getWidth(), it->getHeight()))
		{
			_current = count;
			_redrawFlag = true;
			Control::setFocus(*this);
			return;
		}
		count++;
	}
}

void ComboBox::keyDown(uint32_t keyCode, char character)
{
	if (getHidden()) return;
	switch (keyCode)
	{
	case VK_NUMPAD8:
	case VK_UP:
		if (_current > 0)
		{
			_current--;
			Control::setFocus(*this);
		}
		if (!_isOpen)
			openBox();
		break;
	case VK_NUMPAD2:
	case VK_DOWN:
		if (_current < _entries.size() - 1)
		{
			_current++;
			Control::setFocus(*this);
		}
		if (!_isOpen)
			openBox();
		break;
	case VK_SPACE:
	case VK_RETURN:
		if (_isOpen)
		{
			_selected = _current;
			_selectedControl = _entries[_selected];
			MousePressed(*_selectedControl, 0, 0, 0);
		}
		break;
	case VK_TAB:
		if (_current < _entries.size() - 1)
			_current++;
		break;
	default:
		break;
	}
}

void ComboBox::setRedrawFlag(bool flag)
{
	_redrawFlag = flag;
}

bool ComboBox::getRedrawFlag(void) const
{
	return _redrawFlag;
}

void ComboBox::setBackground(Color color)
{
	for (auto it : _entries)
	{
		it->setBackground(color);
	}
	Control::setBackground(color);
}

void ComboBox::setForeground(Color color)
{
	for (auto it : _entries)
	{
		it->setForeground(color);
	}
	Control::setForeground(color);
}

void ComboBox::setCoords(uint32_t x, uint32_t y)
{
	Control::setCoords(x, y);
	uint32_t h = y;
	for (auto it : _entries)
	{
		it->setCoords(x, h);
		it->setHeight(1);
		h += 1;
	}
}

uint32_t ComboBox::getHeight() const
{
	if (_isOpen)
		return _entries.size() + 1;
	return DEFAULT_HEIGHT;
}

void ComboBox::openBox(void)
{
	for (auto it : _entries)
	{
		if (it == _selectedControl) continue;
		it->setLayer(1);
	}
	setLayer(1);
	_isOpen = true;
}

void ComboBox::closeBox(void)
{
	_isOpen = false;
}
