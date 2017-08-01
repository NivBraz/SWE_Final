#pragma once
#include "MeathodsExceptions.h"
#ifdef MessageBox
#undef MessageBox
#define MessageBox MyMessageBox
#endif
//Default Heigt For Drawing Controls.
#define DEFAULT_HEIGHT 2
//Text To Display In Start Of Checklist String
#define CHECKLIST_TEXT "[ ]"
//Text To Display In Start Of RadioBox String
#define RADIOBOX_TEXT "  "
//Pad Strings With
#define TEXT_PADDING ' '
//Mark Box As Checked
#define BOXCHECK 'X'
//UnmarkBox
#define BOXUNCHECK ' '

//ASCII For Border.
static const char box[] = {'\xDA', '\xBF','\xC0','\xD9','\xB3' ,'\xC4','\xC9','\xBB','\xC8', '\xBC', '\xBA' ,'\xCD'};

enum class Color
{
	Black,
	Blue,
	Green,
	Red,
	Cyan,
	Purple,
	Orange,
	White
};

enum class BorderType
{
	None,
	Single,
	Double
};

enum class MessageBoxReturn
{
	OK,
	Cancel,
	Unclicked
};
