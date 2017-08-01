#pragma once
#include <iostream>
#include "Control.h"
#include <vector>
#include <algorithm>
#include "Defines.h"

/*
*	Panel
*	Derives Functions From Control.
*	Derives CB function - Button::MouseListener.
*	Composite to hold controls.
*/
class Panel : public Control
{
private:
	// Height of Panel
	uint32_t _height;

	// Width of Panel
	uint32_t _width;

	// Holds controls inside panel.
	std::vector<IControl*> _controls;
public:
	//Constructor. _In: height - height of panel, width - width of control.
	Panel(const uint32_t& height = 100, const uint32_t& width = 100);
	~Panel();


	// Inherited via Control
	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override;


	// Adds Contorl to panel. _In: control[ref] - control to add, x - X coords of control, y - Y coords of contorl.
	void addControl(IControl& control, uint32_t x, uint32_t y);


	// Retuns all control inside panel. _Out: fill[ref] - vector to fill.
	void getAllControls(std::vector<Control*>& fill) override;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	void mousePressed(uint32_t x, uint32_t y, bool isLeft) override;


	// What to when mouse is hovered. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	void mouseHover(uint32_t x, uint32_t y, bool isLeft) override;
};
