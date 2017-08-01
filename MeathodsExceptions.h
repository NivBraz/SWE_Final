#pragma once
#include <exception>
#include <string>

class MeathodsExceptions :
	public std::exception
{
public:
	MeathodsExceptions(std::string str = "Meathods Exception!") : _what(str)
	{
	};

protected:
	std::string _what;
};

class OutOfBoundsException :
	public MeathodsExceptions
{
public:
	OutOfBoundsException(std::string str = "Out Of Bounds!") : MeathodsExceptions(str)
	{
	};

	const char* what() const throw() override
	{
		return _what.c_str();
	}
};

class StringWiderThenWidthOfControl :
	public MeathodsExceptions
{
public:
	StringWiderThenWidthOfControl(std::string str = "String Is Wider Then The Width Of The Control!") : MeathodsExceptions(str)
	{
	};

	const char* what() const throw() override
	{
		return _what.c_str();
	}
};

class IndexOutOfBounds :
	public MeathodsExceptions
{
public:
	IndexOutOfBounds(std::string str = "Index Out Of Bounds") : MeathodsExceptions(str)
	{
	};

	const char* what() const throw() override
	{
		return _what.c_str();
	}
};
