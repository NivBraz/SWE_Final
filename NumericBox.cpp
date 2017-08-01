#include "NumericBox.h"


NumericBox::NumericBox(uint32_t width, int32_t min, int32_t max) : Control(width, DEFAULT_HEIGHT, false, true), _value(width - 2), _minBtn(1), _maxBtn(1), _min(min), _max(max), _minusListen(_minBtn, this), _plusListen(_maxBtn, this)
{
	_minBtn.setText("-");
	_minBtn.addListener(_minusListen);
	_maxBtn.setText("+");
	_maxBtn.addListener(_plusListen);
}

NumericBox::~NumericBox()
{
}

int32_t NumericBox::getMin() const
{
	return _min;
}

int32_t NumericBox::getMax() const
{
	return _max;
}

int32_t NumericBox::getValue() const
{
	return std::stoi(_value.getText());
}

bool NumericBox::setValue(int32_t value)
{
	if (value >= _min && value <= _max)
	{
		std::string temp;
		auto stringW = _value.getWidth();
		for (uint32_t i = 0; i < stringW / 2; ++i)
		{
			temp += TEXT_PADDING;
		}
		temp += std::to_string(value);
		_value.setText(temp);
		return true;
	}
	return false;
}

void NumericBox::draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
	if (getHidden()) return;
	if (z == getLayer())
	{
		_minBtn.draw(g, _minBtn.getCoords().X, _minBtn.getCoords().Y, z);
		_value.draw(g, _value.getCoords().X, _value.getCoords().Y, z);
		_maxBtn.draw(g, _maxBtn.getCoords().X, _maxBtn.getCoords().Y, z);
		drawBorder(g, x, y, z);
	}
}

void NumericBox::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
	if (getHidden()) return;
	if (isInside(x, y, _maxBtn.getLeft(), _maxBtn.getTop(), _maxBtn.getWidth(), _maxBtn.getHeight())) // if + pressed
	{
		_maxBtn.mousePressed(x, y, isLeft);
		Control::setFocus(*this);
	}
	if (isInside(x, y, _minBtn.getLeft(), _minBtn.getTop(), _minBtn.getWidth(), _minBtn.getHeight())) // if - pressed
	{
		_minBtn.mousePressed(x, y, isLeft);
		Control::setFocus(*this);
	}
}

void NumericBox::Show(void)
{
	_value.Show();
	_maxBtn.Show();
	_minBtn.Show();
	Control::Show();
}

void NumericBox::Hide(void)
{
	_value.Hide();
	_maxBtn.Hide();
	_minBtn.Hide();
	Control::Hide();
}

void NumericBox::setCoords(uint32_t x, uint32_t y)
{
	_minBtn.setCoords(x, y);
	_value.setCoords(x + 1, y);
	_maxBtn.setCoords(x + _value.getText().size() + 1, y);
	Control::setCoords(x, y);
}

void NumericBox::setBackground(Color color)
{
	_minBtn.setBackground(color);
	_value.setBackground(color);
	_maxBtn.setBackground(color);
	Control::setBackground(color);
}

void NumericBox::setForeground(Color color)
{
	_minBtn.setForeground(color);
	_value.setForeground(color);
	_maxBtn.setForeground(color);
	Control::setForeground(color);
}
