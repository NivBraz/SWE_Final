#pragma once
#include <iostream>
#include <vector>
#include "Control.h"
#include "Defines.h"
#include "Button.h"

/*	==================== ABSTRACT!! =================================
*	Abstract Box - This class is the base class for CheckList and RadioBox.
*	Derives Functions From Control.
*	Derives CB function - Button::MouseListener.
*	Used to hold common data and functionality for Checklist and RadioBox,
*/
class AbstractBox : public Control, public Button::MouseListener
{
protected:
	//Holds Entries.
	std::vector<Button*> _entries;
	//Marks Current Entry.
	uint32_t _current;
public:
	//Constructor. _In: height - height of control, witdh - width of control, entries - text of contorl, prefixString - string to prefix control.
	AbstractBox(uint32_t height, uint32_t width, std::vector<std::string> entries, const std::string& prefixString) throw(StringWiderThenWidthOfControl,std::bad_alloc);
	virtual ~AbstractBox();


	// Inherited via MouseListener
	// CallBack Function when a button is pressed. - unimplemented.
	void MousePressed(Control& control, int x, int y, bool isLeft, Control* msCb = nullptr) override = 0;

	// Inherited via Control
	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	virtual void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button. - unimplemented.
	void mousePressed(uint32_t x, uint32_t y, bool isLeft) override = 0;


	// What to do when key is pressd. _In: keyCode - code of key, character - character pressed. unimplemented.
	void keyDown(uint32_t keyCode, char character) override = 0;


	// Can You move inside this control on tab key.
	bool isTabAble(void) const override;


	// Show Control
	void Show(void) override;


	// Hide Control
	void Hide(void) override;


	// Is this contorl focusable? returns hidden flag.
	bool canGetFocus() const override;


	// Sets controls coords. _In: x - X Coords, y - Y Coords.
	void setCoords(uint32_t x, uint32_t y) override;


	// Gets Height of control
	uint32_t getHeight() const override;
};
