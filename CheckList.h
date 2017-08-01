#pragma once
#include "AbstractBox.h"
#include <algorithm>

/*
*	CheckList
*	Derives Functions From AbstractBox.
*	Used to show and set Checklist properties.
*/
class CheckList : public AbstractBox
{
private:
	// selected check boxes indices.
	std::vector<size_t> _selected;

	// Private function - check ifs if checkbox is to be selected of deselected. _In: index - index of checkbox.
	void selectOrDeselect(uint32_t index);
public:
	//Constructor. _In: height - height of control, witdh - width of control, entries - text of checklist.
	CheckList(uint32_t height, uint32_t width, std::vector<std::string> entries);
	~CheckList();


	// Returns all selected indices
	std::vector<size_t> getSelectedIndices() const;


	// Select an index. _In: index - index to be selected.
	void selectIndex(size_t index) throw (IndexOutOfBounds);


	// deselect an index. _In: index - index to be deselected.
	void deselectIndex(size_t index) throw (IndexOutOfBounds);

	// Inherited via AbstractBox
	// CallBack Function when a checklist is pressed.
	virtual void MousePressed(Control& control, int x, int y, bool isLeft, Control* msCb = nullptr) override;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	virtual void mousePressed(uint32_t x, uint32_t y, bool isLeft) override;


	// What to do when key is pressd. _In: keyCode - code of key, character - character pressed.
	virtual void keyDown(uint32_t keyCode, char character) override;


	// Sets background of control. _In: color - color enum to be selected.
	void setBackground(Color color) override;


	// Sets foreground of control. _In: color - color enum to be selected.
	void setForeground(Color color) override;
};
