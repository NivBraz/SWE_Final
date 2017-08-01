#include "Control.h"

Control* Control::_focused = nullptr;

void Control::draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
}

void Control::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
}

void Control::mouseHover(uint32_t x, uint32_t y, bool isLeft)
{
	return;
}

void Control::keyDown(uint32_t keyCode, char character)
{
}

Control* Control::getFocus()
{
	return _focused;
}

void Control::setFocus(Control& control)
{
	_focused = &control;
	control.setCursorToEnd();
}

void Control::getAllControls(std::vector<Control*>& fill)
{
}


bool Control::canGetFocus() const
{
	return _isFocusable;
}

void Control::setHidden(bool isHidden)
{
	_isHidden = isHidden;
}

bool Control::getHidden(void) const
{
	return _isHidden;
}

bool Control::isClickAble(void) const
{
	return _isClickable;
}

void Control::setCoords(uint32_t x, uint32_t y)
{
	_coords.X = x;
	_coords.Y = y;
}

COORD Control::getCoords(void) const
{
	return _coords;
}

uint32_t Control::getCursorPosition(void) const
{
	return 0;
}

uint32_t Control::getWidth(void) const
{
	return _width;
}

uint32_t Control::getHeight(void) const
{
	return _height;
}

void Control::setHeight(uint32_t height)
{
	_height = height;
}

uint32_t Control::getLeft(void) const
{
	return _coords.X;
}

uint32_t Control::getTop(void) const
{
	return _coords.Y;
}

void Control::setLayer(uint32_t layer)
{
	if (layer < 5)
		_layer = layer;
}

uint32_t Control::getLayer(void) const
{
	return _layer;
}

void Control::setCursorToEnd(void)
{
}

void Control::setBackground(Color color)
{
	_background = color;
}

void Control::setForeground(Color color)
{
	_foreground = color;
}

Color Control::getBackground(void) const
{
	return _background;
}

Color Control::getForeground(void) const
{
	return _foreground;
}

bool Control::isTabAble() const
{
	return false;
}


void Control::Show()
{
	_isHidden = false;
	_layer = 0;
}

void Control::Hide()
{
	_isHidden = true;
	_layer = 5;
}

void Control::setRedrawFlag(bool flag)
{
}

bool Control::getRedrawFlag(void) const
{
	return false;
}

void Control::closeBox()
{
}

void Control::setBorder(BorderType bt)
{
	switch (bt)
	{
	case BorderType::None:
		setBorderDrawer(SimpleBorderFactory::instance().getNull());
		break;
	case BorderType::Single:
		setBorderDrawer(SimpleBorderFactory::instance().getSingle());
		break;
	case BorderType::Double:
		setBorderDrawer(SimpleBorderFactory::instance().getDouble());
		break;
	default:
		break;
	}
}


Control::Control(const uint32_t& width, const uint32_t& height, const bool& isFocusable, const bool& isClickable) : _width(width), _height(height), _isFocusable(isFocusable), _layer(0),
                                                                                                                    _background(Color::Black), _foreground(Color::White), _isHidden(false), _isClickable(isClickable)
{
}

Control::~Control()
{
}

void Control::drawBorder(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
	if (_borderDrawer)
		_borderDrawer->draw(g, getLeft(), getTop(), getWidth(), getHeight());
}
