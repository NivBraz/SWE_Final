#pragma once
#include "Graphics.h"
#include "Borders.h"


class SimpleBorderFactory
{
public:
	const BorderDrawer& getNull()
	{
		return _null;
	}

	const BorderDrawer& getSingle()
	{
		return _single;
	}

	const BorderDrawer& getDouble()
	{
		return _double;
	}

	static SimpleBorderFactory& instance()
	{
		static SimpleBorderFactory instance;
		return instance;
	}

	SimpleBorderFactory(SimpleBorderFactory const&) = delete;
	void operator=(SimpleBorderFactory const&) = delete;
private:
	SimpleBorderFactory();
	NullBorderDrawer _null;
	SingleBorderDrawer _single;
	DoubleBorderDrawer _double;
};
