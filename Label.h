#pragma once
#include <iostream>
#include "Defines.h"
#include "Control.h"

/*
*	Label
*	Derives Functions From Control.
*	Used to show and set label properties.
*/
class Label : public Control
{
private:
	// Text to be displayed.
	std::string _value;
public:
	// Constructor. _In: width - width of control.
	Label(uint32_t width);
	~Label();


	// Sets Label text. _In: value - string to be displayed in button.
	void setText(std::string value) throw(StringWiderThenWidthOfControl);


	// Gets Label text. Returns string - text of button.
	std::string getText(void) const;


	// Inherited via Control
	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override;
};
