#pragma once
#include "Control.h"
#include "Defines.h"
#include "Label.h"
#include "Button.h"

/*
*	MessageBox
*	Derives Functions From Control.
*	Derives CB function - Button::MouseListener.
*	Used to show and set MessageBox properties.
*/
class MyMessageBox : public Control, public Button::MouseListener
{
private:
	// Holds Title of MessageBox.
	Label _title;

	// Holds text of MessageBox.
	Label _text;

	// Ok Button.
	Button _ok;

	// Cancel Button.
	Button _cancel;

	// Private Function - Set all controls to max layer.
	void setLayersToMax();

	// Holds return value - what button was pressed.
	MessageBoxReturn _mbr;
public:
	// Constructor.  _In: witdh - width of control, height  - height of control.
	MyMessageBox(uint32_t height, uint32_t width);
	~MyMessageBox();

	// Sets MessageBox text. _In: text to display.
	void setText(const std::string& text);


	// Sets MessageBox title. _In: text to display.
	void setTitle(const std::string& title);


	// Inherited via Control
	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	virtual void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	void mousePressed(uint32_t x, uint32_t y, bool isLeft) override;


	// Shows Messagebox.
	void Show(void) override;


	// Hides MessageBox
	void Hide(void) override;


	// Sets controls coords. _In: x - X Coords, y - Y Coords.
	void setCoords(uint32_t x, uint32_t y) override;


	// Sets background of control. _In: color - color enum to be selected.
	void setBackground(Color color) override;


	// Sets foreground of control. _In: color - color enum to be selected.
	void setForeground(Color color) override;


	// Returns what button was clicked.
	MessageBoxReturn getReturnValue(void) const;


	// Inherited via MouseListener
	// CallBack Function when a messagebox button is pressed.
	virtual void MousePressed(Control& b, int x, int y, bool isLeft, Control* msCb = nullptr) override;
};
