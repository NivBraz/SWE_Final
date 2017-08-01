#include "Borders.h"
#include <iostream>

void drawMe(Graphics& g, uint32_t left, uint32_t top, uint32_t width, uint32_t height, BorderType bt)
{
	g.setBackground(Color::Black);
	int32_t a, col, row;
	auto style = (static_cast<int>(bt) - 1) * 6;


	char tl, tr, bl, br, side, edge, shadow;
	tl = box[style];
	tr = box[style + 1];
	bl = box[style + 2];
	br = box[style + 3];
	side = box[style + 4];
	edge = box[style + 5];
	std::string Side;
	Side += side;

	std::string Line(width, edge);

	col = left;
	row = top;
	g.write(left - 1, top - 1, tl + Line + tr);
	for (a = 1; a < height; a++)
	{
		g.write(col - 1, row + a - 1, Side);
		g.write(col + width, (row + a) - 1, Side);
	}

	g.write(col - 1, (height + row) - 1, bl + Line + br);
}

void SingleBorderDrawer::draw(Graphics& g, uint32_t left, uint32_t top, uint32_t width, uint32_t height) const
{
	drawMe(g, left, top, width, height, BorderType::Single);
}


void NullBorderDrawer::draw(Graphics& g, uint32_t left, uint32_t top, uint32_t width, uint32_t height) const
{
}

void DoubleBorderDrawer::draw(Graphics& g, uint32_t left, uint32_t top, uint32_t width, uint32_t height) const
{
	drawMe(g, left, top, width, height, BorderType::Double);
}
