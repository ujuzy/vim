#pragma once

#include "IObservable.h"
#include "Model.h"
#include "Draw.h"
#include "iostream"

class View : IObservable
{
public:
	View(Model*);
	virtual void SetCursor(unsigned int, unsigned int);
	virtual void UpdateScrolling(unsigned int, unsigned int, std::vector<MyString>&);
	virtual void UpdateLine(unsigned int, MyString);
	virtual void PrepareForCommand();
	virtual void ClearForCommand(unsigned int, unsigned int);
	virtual void ShowInput(char);
	virtual void ShowStatusBar(MyString, MyString, unsigned int, unsigned int);
	virtual void ShowHelp();
	virtual void ClearAll();
};

