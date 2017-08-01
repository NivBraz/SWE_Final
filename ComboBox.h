#pragma once
#include <iostream>
#include <vector>
#include "Control.h"
#include "Defines.h"
#include "Button.h"
#include <algorithm>

/*
*	ComboBox
*	Derives Functions From Control.
*	Derives CB function - Button::MouseListener.
*	Used to show and set ComboBox properties.
*/

class ComboBox : public Control, public Button::MouseListener
{
private:
	// Holds entries of ComboBox.
	std::vector<Button*> _entries;

	// Holds selected index.
	size_t _selected;

	// Holds Current Selected contorl inside ComboBox.
	Button* _selectedControl;

	// Marks Current Entry.
	uint32_t _current;

	// Variable to check whether ComboBox is open or closed. 
	bool _isOpen;

	// Variable to check whether ComboBox needs to be redrawed.
	bool _redrawFlag;

	// Private function - manages layers and opens ComboBox.
	void openBox(void);
public:
	// Constructor. _In: witdh - width of control, entries - text of contorl.
	ComboBox(uint32_t width, std::vector<std::string> entries);
	~ComboBox();

	// Closes ComboBox once user has pressed tab, or clicked outside of ComboBox.
	void closeBox(void) override;


	// Returns selected index
	size_t getSelectedIndex(void) const;


	// Select an index. _In: index - index to be selected.
	void setSelectedIndex(size_t index) throw (IndexOutOfBounds);


	// Inherited via Control
	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	virtual void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	void mousePressed(uint32_t x, uint32_t y, bool isLeft) override;


	// What to when mouse is hovered. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	void mouseHover(uint32_t x, uint32_t y, bool isLeft) override;


	// What to do when key is pressd. _In: keyCode - code of key, character - character pressed.
	void keyDown(uint32_t keyCode, char character) override;


	// Sets if we need to redraw contorl. _In: flag - true/false.
	void setRedrawFlag(bool flag) override;


	// Sets background of control. _In: color - color enum to be selected.
	void setBackground(Color color) override;


	// Sets foreground of control. _In: color - color enum to be selected.
	void setForeground(Color color) override;


	// Sets controls coords. _In: x - X Coords, y - Y Coords.
	void setCoords(uint32_t x, uint32_t y) override;


	// Gets Height of control
	uint32_t getHeight() const override;


	// Returns whether control needs to be redrawed. 
	bool getRedrawFlag(void) const override;


	// Inherited via MouseListener
	// CallBack Function when a comboBox item is pressed.
	virtual void MousePressed(Control& control, int x, int y, bool isLeft, Control* msCb = nullptr) override;
};
