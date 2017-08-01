#pragma once
#include <iostream>
#include "Control.h"
#include "Defines.h"

/*	
*	Button
*	Derives Functions From Control.
*	Used to show and set button properties.
*/
class Button : public Control
{
public:
	// CallBack Function - What to do when button is press. unimplemented.
	// _In: b - control pressed[ref], x - X coords of press, y - Y coords of press, isLeft - is press mouse left button,  mbCB - another control to be used on callback
	// _Out: mbCB - points to control passed for changed.
	struct MouseListener
	{
		virtual void MousePressed(Control& b, int x, int y, bool isLeft, Control* mbCb = nullptr) = 0;
	};


	// Constructor. width - width of control.
	explicit Button(uint32_t width);
	~Button();


	// Sets button text. _In: value - string to be displayed in button.
	void setText(std::string value) throw(StringWiderThenWidthOfControl,std::bad_alloc);


	// Gets button text. Returns string - text of button.
	std::string getText(void) const;


	// Adds Callback function for button. _In: listener - CB funciton.
	void addListener(MouseListener& listener);


	// Inherited via Control
	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	virtual void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button. - unimplemented.
	void mousePressed(uint32_t x, uint32_t y, bool isLeft) override;

private:
	// Holds button text value.
	std::string _value;
	// Holds Callback function.
	MouseListener* ml;
};
