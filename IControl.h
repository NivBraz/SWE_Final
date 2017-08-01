#pragma once
#include <iostream>
#include "Graphics.h"

class IControl
{
public:
	IControl();
	virtual ~IControl();
	virtual void draw(Graphics& g, uint32_t x, uint32_t y, uint32_t z) const = 0;
	virtual void setCoords(uint32_t x, uint32_t y);
};
