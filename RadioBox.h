#pragma once
#include "AbstractBox.h"

/*
*	RadioBox
*	Derives Functions From AbstractBox.
*	Used to show and set RadioBox properties.
*/
class RadioBox : public AbstractBox
{
private:
	// selected RadioBox index.
	size_t _selected;

	// Private function - cleans checked mark from all controls.
	void ClearAstrix();
public:
	//Constructor. _In: height - height of control, witdh - width of control, entries - text of RadioBox.
	RadioBox(uint32_t height, uint32_t width, std::vector<std::string> entries);
	~RadioBox();


	// Returns selected index.
	size_t getSelectedIndex() const;


	// Select an index. _In: index - index to be selected.
	void setSelectedIndex(size_t index) throw(IndexOutOfBounds);


	// Inherited via MouseListener
	// CallBack Function when a checklist is pressed.
	virtual void MousePressed(Control& control, int x, int y, bool isLeft, Control* msCb = nullptr) override;


	// Inherited via Control
	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	void mousePressed(uint32_t x, uint32_t y, bool isLeft) override;


	// What to do when key is pressd. _In: keyCode - code of key, character - character pressed.
	void keyDown(uint32_t keyCode, char character) override;


	// Sets background of control. _In: color - color enum to be selected.
	void setBackground(Color color) override;


	// Sets foreground of control. _In: color - color enum to be selected.
	void setForeground(Color color) override;
};
