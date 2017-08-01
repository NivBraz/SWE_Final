#pragma once
#include "Graphics.h"

struct BorderDrawer
{
	virtual void draw(Graphics& g, uint32_t left, uint32_t top, uint32_t width, uint32_t height) const = 0;
};

class SingleBorderDrawer : public BorderDrawer
{
public:
	void draw(Graphics& g, uint32_t left, uint32_t top, uint32_t width, uint32_t height) const override;
};

class NullBorderDrawer : public BorderDrawer
{
public:
	void draw(Graphics& g, uint32_t left, uint32_t top, uint32_t width, uint32_t height) const override;
};

class DoubleBorderDrawer : public BorderDrawer
{
public:
	void draw(Graphics& g, uint32_t left, uint32_t top, uint32_t width, uint32_t height) const override;
};
