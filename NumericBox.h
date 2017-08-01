#pragma once
#include <iostream>
#include "Control.h"
#include "Defines.h"
#include "Label.h"
#include "Button.h"

/*
*	NumericBox
*	Derives Functions From Control.
*	Derives CB function - Button::MouseListener.
*	Used to show and set NumericBox properties.
*/
class NumericBox : public Control
{
private:
	// Holds minimum value of control.
	int32_t _min;

	// Holds maximum value of control.
	int32_t _max;

	// Shows control value.
	Label _value;

	// Button to decrement.
	Button _minBtn;

	// Button to increment.
	Button _maxBtn;

	// Plus button callback
	struct plusListener : public Button::MouseListener
	{
		plusListener(Control& c, NumericBox* wrapingObj) : _c(c), _wrappingObj(wrapingObj)
		{
		}

		void MousePressed(Control& b, int x, int y, bool isLeft, Control* mbCb = nullptr) override
		{
			auto valAfterAction = _wrappingObj->getValue() + 1;
			if (valAfterAction >= _wrappingObj->getMin() && valAfterAction <= _wrappingObj->getMax())
				_wrappingObj->setValue(valAfterAction);
		}

	private:
		Control& _c;
		NumericBox* _wrappingObj;
	};

	// Minus button callback
	struct minusListener : public Button::MouseListener
	{
		minusListener(Control& c, NumericBox* wrapingObj) : _c(c), _wrappingObj(wrapingObj)
		{
		}

		void MousePressed(Control& b, int x, int y, bool isLeft, Control* mbCb = nullptr) override
		{
			auto valAfterAction = _wrappingObj->getValue() - 1;
			if (valAfterAction >= _wrappingObj->getMin() && valAfterAction <= _wrappingObj->getMax())
				_wrappingObj->setValue(valAfterAction);
		}

	private:
		Control& _c;
		NumericBox* _wrappingObj;
	};

	// Minus listener
	minusListener _minusListen;

	// Plus listener
	plusListener _plusListen;
public:
	// Constructor.  _In: witdh - width of control, min - minumum value of control, max - maximum value of control.
	NumericBox(uint32_t width, int32_t min, int32_t max);
	~NumericBox();


	// Returns min value of control.
	int32_t getMin() const;


	// Returns max value of control.
	int32_t getMax() const;


	// Returns value of control.
	int32_t getValue() const;


	// Sets value of control. _In: value - value to set.
	bool setValue(int32_t value);


	// Inherited via Control
	// Draws Control. _In: g - Graphics Drawer, x - X Coords, y - Y Coords, Z - Layer.
	virtual void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const override;


	// What to when mouse is pressed. _In: x - X Coords of press, y - Y coords of press, isLeft - is press mouse left button.
	void mousePressed(uint32_t x, uint32_t y, bool isLeft) override;


	// Shows NumericBox
	void Show(void) override;


	// Hides NumericBox
	void Hide(void) override;


	// Sets controls coords. _In: x - X Coords, y - Y Coords.
	void setCoords(uint32_t x, uint32_t y) override;


	// Sets background of control. _In: color - color enum to be selected.
	void setBackground(Color color) override;


	// Sets foreground of control. _In: color - color enum to be selected.
	void setForeground(Color color) override;
};
