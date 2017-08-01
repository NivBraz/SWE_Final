#pragma once
#include "IControl.h"
#include <vector>
#include "SimpleBorderFactory.h"

/*	==================== ABSTRACT!! =================================
*	Abstract Box - This class is the base class for CheckList and RadioBox.
*	Derives Functions From IControl.
*	Used to hold common data and functionality for all controls.
*/
class Control : public IControl
{
private:
	// Holds width of control.
	uint32_t _width;

	// Holds height of control.
	uint32_t _height;

	// Holds coords of control.
	COORD _coords;

	// Can control be focused?
	bool _isFocusable;

	// Current control in focus.
	static Control* _focused;

	// Layer of control.
	uint32_t _layer;

	// Colors of control.
	Color _background, _foreground;

	// Is Control Hidden?
	bool _isHidden;

	// Can Control be clicked on?
	bool _isClickable;

	// Holds border drawer cb function. 
	const BorderDrawer* _borderDrawer;
public:
	// Constructor. _In: width - width of control, height - height of control, isFocusable - can control be focused?, isClickable - can control be clicked on?.
	Control(const uint32_t& width, const uint32_t& height, const bool& isFocusable, const bool& isClickable);
	~Control();

	// Draws Control Border. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	void drawBorder(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const;


	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer. unimplemented polymorphic.
	void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override = 0;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button. - unimplemented polymorphic.
	virtual void mousePressed(uint32_t x, uint32_t y, bool isLeft);


	// What to when mouse is hovered. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button. - unimplemented polymorphic.
	virtual void mouseHover(uint32_t x, uint32_t y, bool isLeft);

	// What to do when key is pressd. _In: keyCode - code of key, character - character pressed. - unimplemented polymorphic.
	virtual void keyDown(uint32_t keyCode, char character);


	// Retuns all control inside panel. _Out: fill[ref] - vector to fill. - unimplemented polymorphic.
	virtual void getAllControls(std::vector<Control*>& fill);


	// Retuns control in current focus.
	static Control* getFocus();


	// Sets Control in focus. _In: control[ref] - control to be focused.
	static void setFocus(Control& control);


	// Returns whether control can gain focus.
	virtual bool canGetFocus() const;

	// Sets Hidden flag. _In isHidden - true/false.
	void setHidden(bool isHidden);


	// Gets hidden flag.
	bool getHidden(void) const;


	// Returns whether control is clickable.
	bool isClickAble(void) const;


	// Sets controls coords. _In: x - X Coords, y - Y Coords.
	void setCoords(uint32_t x, uint32_t y) override;


	// Returns control's coords.
	COORD getCoords(void) const;


	// Returns Current cursor position. - unimplemented polymorphic. 
	virtual uint32_t getCursorPosition(void) const;


	// Returns control's width.
	uint32_t getWidth(void) const;


	// Returns control's height.
	virtual uint32_t getHeight(void) const;


	// Sets control's height. _In: height - height to set.
	void setHeight(uint32_t height);


	// Returns X coords.
	uint32_t getLeft(void) const;


	// Returns y coords.
	uint32_t getTop(void) const;


	// Sets control's layer. _In: layer - layer to be set/
	void setLayer(uint32_t layer);


	// Returns control's layer.
	uint32_t getLayer(void) const;


	// Set Cursor to end to text. - unimplemented polymorphic. 
	virtual void setCursorToEnd(void);


	// Sets background of control. _In: color - color enum to be selected.
	virtual void setBackground(Color color);


	// Sets foreground of control. _In: color - color enum to be selected.
	virtual void setForeground(Color color);


	// Gets control's background.
	virtual Color getBackground(void) const;


	// Gets control's foreground.
	virtual Color getForeground(void) const;


	// Can You move to this control on tab key.
	virtual bool isTabAble(void) const;


	// Shows contorl
	virtual void Show(void);


	// Hides contorl.
	virtual void Hide(void);


	// Sets if we need to redraw contorl. _In: flag - true/false.
	virtual void setRedrawFlag(bool flag);


	// Returns whether control needs to be redrawed. 
	virtual bool getRedrawFlag(void) const;


	// Closes ComboBox. - unimplemented.
	virtual void closeBox();

	// Used to sort by layer.
	struct less_than_key
	{
		inline bool operator()(IControl* struct1, IControl* struct2) const
		{
			return (dynamic_cast<Control*>(struct1)->getLayer() > dynamic_cast<Control*>(struct2)->getLayer());
		}
	};


	// Set border type. _In: bt - bordertype enum.
	virtual void setBorder(BorderType bt);


	// Sets Border Drawer cb function.
	virtual void setBorderDrawer(const BorderDrawer& borderDrawer)
	{
		_borderDrawer = &borderDrawer;
	}
};
