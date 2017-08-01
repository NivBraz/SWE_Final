#include "EventEngine.h"
#include <functional>

EventEngine::EventEngine(DWORD input, DWORD output)
	: _graphics(output), _console(GetStdHandle(input))
{
	GetConsoleMode(_console, &_consoleMode);
	SetConsoleMode(_console, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void EventEngine::run(Control& c)
{
	for (bool redraw = true;;)
	{
		if (redraw)
		{
			_graphics.clearScreen();
			_graphics.setCursorVisibility(false);
			for (size_t p = 0; p < 5; ++p)
				c.draw(_graphics, 0, 0, p);
			redraw = false;
			Control::getFocus()->setRedrawFlag(false);
			auto t = Control::getFocus()->getCoords();

			_graphics.moveTo(t.X + Control::getFocus()->getCursorPosition(), t.Y);
		}

		INPUT_RECORD record;
		DWORD count;
		ReadConsoleInput(_console, &record, 1, &count);
		switch (record.EventType)
		{
		case KEY_EVENT:
			{
				auto f = Control::getFocus();
				if (f != nullptr && record.Event.KeyEvent.bKeyDown)
				{
					auto code = record.Event.KeyEvent.wVirtualKeyCode;
					auto chr = record.Event.KeyEvent.uChar.AsciiChar;
					if (code == VK_TAB)
						if (f->isTabAble())
							f->keyDown(code, chr);
						else
							moveFocus(c, f);
					else
						f->keyDown(code, chr);
					redraw = true;
				}
				break;
			}
		case MOUSE_EVENT:
			{
				auto button = record.Event.MouseEvent.dwButtonState;
				auto coord = record.Event.MouseEvent.dwMousePosition;
				auto x = coord.X - c.getLeft();
				auto y = coord.Y - c.getTop();
				if (button == FROM_LEFT_1ST_BUTTON_PRESSED || button == RIGHTMOST_BUTTON_PRESSED)
				{
					c.mousePressed(x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED);
					redraw = true;
				}
				else
				{
					c.mouseHover(x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED);
					redraw = Control::getFocus()->getRedrawFlag();
				}
				break;
			}
		case WINDOW_BUFFER_SIZE_EVENT:
			redraw = true;
			break;
		default:
			break;
		}
	}
}

EventEngine::~EventEngine()
{
	SetConsoleMode(_console, _consoleMode);
}

void EventEngine::moveFocus(Control& main, Control* focused)
{
	std::vector<Control*> controls;
	main.getAllControls(controls);
	auto it = std::find(controls.begin(), controls.end(), focused);
	do
		if (++it == controls.end())
			it = controls.begin();
	while (!(*it)->canGetFocus());
	if (focused != *it) focused->closeBox();
	Control::setFocus(**it);
}
