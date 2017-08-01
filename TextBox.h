#pragma once
#include <iostream>
#include "Control.h"
#include "Defines.h"
#include "Button.h"

/*
*	TextBox
*	Derives Functions From Contorl.
*	Used to show and set TextBox properties.
*/
class TextBox : public Control
{
private:
	// Holds value of TextBox
	std::string _value;

	// Holds current cursor position in TextBox
	uint32_t _cursorPosition;
public:
	// Constructor. _In: width - width of control.
	TextBox(uint32_t width);
	~TextBox();

	// Sets TextBox's text. _In value - text to be displayed.
	void setText(std::string value) throw(StringWiderThenWidthOfControl);


	// Sets TextBox's text. _In value - text to be displayed.
	void setText(std::wstring value);

	// Inherited via Control
	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	void mousePressed(uint32_t x, uint32_t y, bool isLeft) override;


	// What to do when key is pressd. _In: keyCode - code of key, character - character pressed.
	void keyDown(uint32_t keyCode, char character) override;


	// Returns TextBox's text.
	std::string getText(void) const;


	// Returns current cursor position.
	uint32_t getCursorPosition(void) const override;


	// Set Cursor to end to text.
	void setCursorToEnd(void) override;
};
