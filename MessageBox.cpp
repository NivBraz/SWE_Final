#include "MessageBox.h"
#define OK_BUTTON_WIDTH 2
#define CANCEL_BUTTON_WIDTH 6

MyMessageBox::MyMessageBox(uint32_t height, uint32_t width) : Control(width, height, false, true), _title(width), _text(width), _ok(OK_BUTTON_WIDTH), _cancel(CANCEL_BUTTON_WIDTH), _mbr(MessageBoxReturn::Unclicked)
{
	_ok.setText("OK");
	_ok.addListener(*this);

	_cancel.setText("Cancel");
	_cancel.addListener(*this);

	setLayersToMax(); // show message box top of every control.
}


MyMessageBox::~MyMessageBox()
{
}

void MyMessageBox::setText(const std::string& text)
{
	_text.setText(text);
}

void MyMessageBox::setTitle(const std::string& title)
{
	_title.setText(title);
}

void MyMessageBox::draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const
{
	if (getHidden()) return;
	if (z == getLayer())
	{
		g.clearScreen((getWidth() * getHeight() * 5), getCoords().X, getCoords().Y);
		uint32_t h = this->getCoords().Y;
		_title.draw(g, _title.getCoords().X, _title.getCoords().Y, z);
		_text.draw(g, _text.getCoords().X, _text.getCoords().Y, z);
		_ok.draw(g, _ok.getCoords().X, _ok.getCoords().Y, z);
		_cancel.draw(g, _cancel.getCoords().X, _cancel.getCoords().Y, z);
		drawBorder(g, x, y, z);
	}
}

void MyMessageBox::mousePressed(uint32_t x, uint32_t y, bool isLeft)
{
	if (getHidden()) return;
	if (isInside(x, y, _ok.getLeft(), _ok.getTop(), _ok.getWidth(), _ok.getHeight()))
	{
		_mbr = MessageBoxReturn::OK;
		_ok.mousePressed(x, y, isLeft);
		Control::setFocus(*this);
	}
	if (isInside(x, y, _cancel.getLeft(), _cancel.getTop(), _cancel.getWidth(), _cancel.getHeight()))
	{
		_mbr = MessageBoxReturn::Cancel;
		_cancel.mousePressed(x, y, isLeft);
		Control::setFocus(*this);
	}
}

void MyMessageBox::Show()
{
	_ok.Show();
	_cancel.Show();
	_text.Show();
	_title.Show();
	Control::Show();
	setLayersToMax();
}

void MyMessageBox::Hide()
{
	_ok.Hide();
	_cancel.Hide();
	_text.Hide();
	_title.Hide();
	Control::Hide();
}

void MyMessageBox::setCoords(uint32_t x, uint32_t y)
{
	auto h = getHeight();
	auto btnPos = (y + h - h / 8) < (y + h - 2) ? (y + h - h / 8) : (y + h - 2); // calculate buttons Y position inside Messagebox.
	Control::setCoords(x, y);
	_title.setCoords(x, y);

	_text.setCoords(x + getWidth() / 4, y + getHeight() / 2);
	_ok.setCoords(x + (getWidth() / 4) * 3, btnPos);
	_cancel.setCoords(x + getWidth() / 4, btnPos);
}

void MyMessageBox::setBackground(Color color)
{
	_ok.setBackground(color);
	_cancel.setBackground(color);
	_text.setBackground(color);
	_title.setBackground(color);
	Control::setBackground(color);
}

void MyMessageBox::setForeground(Color color)
{
	_ok.setForeground(color);
	_cancel.setForeground(color);
	_text.setForeground(color);
	_title.setForeground(color);
	Control::setForeground(color);
}

MessageBoxReturn MyMessageBox::getReturnValue() const
{
	return _mbr;
}

void MyMessageBox::MousePressed(Control& b, int x, int y, bool isLeft, Control* msCb)
{
	this->Hide();
}

void MyMessageBox::setLayersToMax()
{
	_ok.setLayer(4);
	_cancel.setLayer(4);
	_text.setLayer(4);
	_title.setLayer(4);
	setLayer(4);
}
