#pragma warning(disable:4996)
#include "EventEngine.h"
#include "TextBox.h"
#include "Label.h"
#include "Button.h"
#include "Panel.h"
#include "NumericBox.h"
#include "ComboBox.h"
#include "RadioBox.h"
#include "CheckList.h"
#include "Defines.h"
#include "MessageBox.h"
#include <string>
#include <iostream>
using namespace std;
static int y = 2;

struct ControlData
{
	string _controlType;
	string _controlName;
	uint32_t _controlNumber;
	void* _data;
};

struct MyListener : public Button::MouseListener
{
	MyListener(Control& c, Control* mbCb) : _c(c), _mbCb(mbCb)
	{
	}

	void MousePressed(Control& b, int x, int y, bool isLeft, Control* mbCb) override
	{
		_c.setForeground(Color::Green);
		_mbCb->Show();
	}

private:
	Control& _c;
	Control* _mbCb;
};

int showMenu() {
	int choice;
	cout << "please select box type:" << endl;
	cout << "1 - text box" << endl;
	cout << "2 - combo box" << endl;
	cout << "3 - radio box" << endl;
	cout << "4 - check list" << endl;
	cout << "5 - numeric box" << endl;
	cout << "0 - RUN" << endl;
	cin >> choice;
	if ((choice < 0) || (choice>5)) {
		cout << "wrong input !";
		return showMenu();
	}
	return choice;
}
Label* setLabel() {
	Label* label;
	string name;
	cout << "please enter label name:" << endl;
	cin.ignore();
	getline(cin, name);
	label = new Label(20);
	(*label).setText(name);
	return label;
}
TextBox* setTextBox() {
	TextBox* tbox;
	int width;
	string name;
	string placeHolder;
	cout << "please enter text box width:" << endl;
	cin >> width;
	cout << "please enter text box place holder:" << endl;
	cin.ignore();
	getline(cin,placeHolder);
	tbox = new TextBox(width);
	(*tbox).setText(placeHolder);
	(*tbox).setBorder(BorderType::Single);
	return tbox;
}

ComboBox* setComboBox()
{
	ComboBox* cbox;
	int width;
	int x = 0;
	vector<string> entries;
	string name;
	string placeHolder;
	cout << "please enter combo box width:" << endl;
	cin >> width;
	cout << "please enter number of options:" << endl;
	cin >> x;
	for (int i = 0; i < x; i++)
	{
		cout << "enter an option value" << endl;
		cin.ignore();
		getline(cin, placeHolder);
		entries.push_back(placeHolder);
	}
	cbox = new ComboBox(width, entries);
	(*cbox).setSelectedIndex(1);
	(*cbox).setBorder(BorderType::Single);
	(*cbox).setBackground(Color::Cyan);
	return cbox;
}

RadioBox* setRadioBox()
{
	RadioBox* rbox;
	int width;
	int height = 0;
	vector<string> entries;
	string name;
	string placeHolder;
	cout << "please enter radio box width:" << endl;
	cin >> width;
	cout << "please enter number of options:" << endl;
	cin >> height;
	for (int i = 0; i < height; i++)
	{
		cout << "enter an option value" << endl;
		cin.ignore();
		getline(cin, placeHolder);
		entries.push_back(placeHolder);
	}
	rbox = new RadioBox(height, width, entries);
	(*rbox).setBorder(BorderType::Single);
	(*rbox).setBackground(Color::Red);
	return rbox;
}

CheckList* setCheckList()
{
	CheckList* clist;
	int width;
	int height = 0;
	vector<string> entries;
	string name;
	string placeHolder;
	cout << "please enter check list width:" << endl;
	cin >> width;
	cout << "please enter number of options:" << endl;
	cin >> height;
	for (int i = 0; i < height; i++)
	{
		cout << "enter an option value" << endl;
		cin.ignore();
		getline(cin, placeHolder);
		entries.push_back(placeHolder);
	}
	clist = new CheckList(height, width, entries);
	(*clist).setBorder(BorderType::Double);
	(*clist).setBackground(Color::Orange);
	return clist;
}

NumericBox* setNumericBox()
{
	NumericBox* nbox;
	int width;
	int min;
	int max;
	int default;
	cout << "please enter numeric box width:" << endl;
	cin >> width;
	cout << "please select minimum number" << endl;
	cin >> min;
	cout << "please select maximum number" << endl;
	cin >> max;
	cout << "please select default number" << endl;
	cin >> default;
	nbox = new NumericBox(width, min, max);
	(*nbox).setBorder(BorderType::Single);
	(*nbox).setBackground(Color::Blue);
	(*nbox).setValue(default);
	return nbox;

	
}

int main(int argc, char** argv)
{
	int ch = 1;
	Panel main;
	Label* tlabel;
	TextBox* tbox = NULL;
	ComboBox* cbox = NULL;
	RadioBox* rbox = NULL;
	CheckList* clist = NULL;
	NumericBox* nbox = NULL;
	try
	{
		
		MessageBox mb(15, 25);
		mb.setText("Thank You");
		mb.setTitle("your form has been submit");
		mb.Hide();
	while(ch){
		ch = showMenu();
		switch (ch) {
		case 1:
			tlabel = setLabel();
			tbox = setTextBox();
			main.addControl((*tlabel), 1, y);
			main.addControl((*tbox), 25, y);
			y += 3;
			break;
		case 2:
			tlabel = setLabel();
			cbox = setComboBox();
			main.addControl((*tlabel), 1, y);
			main.addControl((*cbox), 25, y);
			y += 3;
			break;
		case 3:
			tlabel = setLabel();
			rbox = setRadioBox();
			main.addControl((*tlabel), 1, y);
			main.addControl((*rbox), 25, y);
			y += rbox->getHeight() +1;
			break;
		case 4:
			tlabel = setLabel();
			clist = setCheckList();
			main.addControl((*tlabel), 1, y);
			main.addControl((*clist), 25, y);
			y += clist->getHeight() + 1;
			break;
		case 5:
			tlabel = setLabel();
			nbox = setNumericBox();
			main.addControl((*tlabel), 1, y);
			main.addControl((*nbox), 25, y);
			y += 3;
			break;
		case 0:
			break;
		}
		
	}
		
		Button bSubmit(10);
		bSubmit.setText("Submit");
		MyListener listener(bSubmit, &mb);
		bSubmit.addListener(listener);
		bSubmit.setBorder(BorderType::Double);

		main.addControl(mb, 10, 10);
		mb.setBorder(BorderType::Single);
		main.addControl(bSubmit, 1, y+1);
		Control::setFocus(*tbox);
		EventEngine engine;
		engine.run(main);
	}
	catch (exception& e)
	{
		cerr << e.what();
	}
	return 0;
}
