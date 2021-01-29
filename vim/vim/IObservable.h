#pragma once

#include <vector>
#include <MyString.h>

class IObservable
{
public:
	virtual void SetCursor(unsigned int, unsigned int) = 0;
	virtual void UpdateScrolling(unsigned int, unsigned int, std::vector<MyString>&) = 0;
	virtual void UpdateLine(unsigned int, MyString) = 0;
	virtual void PrepareForCommand() = 0;
	virtual void ClearForCommand(unsigned int, unsigned int) = 0;
	virtual void ShowInput(char) = 0;
	virtual void ShowStatusBar(MyString, MyString, unsigned int, unsigned int) = 0;
	virtual void ShowHelp() = 0;
	virtual void ClearAll() = 0;
};