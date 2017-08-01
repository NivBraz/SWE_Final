#include "AbstractBox.h"


AbstractBox::AbstractBox(uint32_t height, uint32_t width, std::vector<std::string> entries, const std::string& prefixString) : Control(width, height * _entries.size(), true, true), _current(0)
{
	for (uint32_t i = 0; i < entries.size(); ++i)
	{
		if (entries[i].size() > width)
			throw StringWiderThenWidthOfControl(); // if string is wider then control throw exception.
		_entries.push_back(new Button(width));
	}

	auto _it = _entries.begin();

	for (auto it : entries)
	{
		(*_it)->setText(prefixString + it);

		(*_it)->addListener(*this);
		++_it;
	}
}

AbstractBox::~AbstractBox()
{
	Button* ptr;
	for (auto it : _entries)
	{
		ptr = it;
		delete ptr;
	}
}


void AbstractBox::draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
	if (getHidden()) return;
	if (z == getLayer())
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
		drawBorder(g, x, y, z);
	}
}


bool AbstractBox::isTabAble(void) const
{
	if (_current == _entries.size() - 1 || getHidden()) return false; // if we're done with elements, tab will go to next control.
	return true;
}

void AbstractBox::Show(void)
{
	setHidden(false);
	for (auto it : _entries)
	{
		it->Show();
	}
}

void AbstractBox::Hide(void)
{
	setHidden(true);
	for (auto it : _entries)
	{
		it->Hide();
	}
}

bool AbstractBox::canGetFocus(void) const
{
	return !getHidden();
}

void AbstractBox::setCoords(uint32_t x, uint32_t y)
{
	Control::setCoords(x, y);
	uint32_t h = y;
	uint32_t counter = 0;

	for (auto it : _entries)
	{
		it->setCoords(x, h);
		h += DEFAULT_HEIGHT;
	}
}

uint32_t AbstractBox::getHeight() const
{
	return DEFAULT_HEIGHT * _entries.size();
}
