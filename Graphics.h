#pragma once

#include <string>
#include <Windows.h>
#include "Defines.h"
#include <io.h>
#include <fcntl.h>
using namespace std;


class Graphics
{
public:
	Graphics(DWORD stdHandle = STD_OUTPUT_HANDLE);
	void clearScreen() const;
	void moveTo(int x, int y);
	void setBackground(Color color);
	void setForeground(Color color);
	void write(const string& s);
	void write(int x, int y, const string& s);
	void write(wstring s);
	void write(int x, int y, wstring s);
	void setCursorVisibility(bool isVisible);
	void moveCursor(COORD c);
	void clearScreen(uint32_t size, uint8_t x, uint8_t y) const;
private:
	HANDLE _console;
	Color _background, _foreground;

	void updateConsoleAttributes();
};

bool isInside(int x, int y, int left, int top, int width, int height);
