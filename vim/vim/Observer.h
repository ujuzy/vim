#pragma once

#include "MyString.h"
#include "IObservable.h"

class Observer
{
public:
	void AddObserver(IObservable*);
	void NotifySetCursor(unsigned int, unsigned int);
	void NotifyUpdateScrolling(unsigned int, unsigned int, std::vector<MyString>&);
	void NotifyUpdateLine(unsigned int, MyString);
	void NotifyPrepareForCommand();
	void NotifyClearForCommand(unsigned int, unsigned int);
	void NotifyShowInput(char);
	void NotifyShowStatusBar(MyString, MyString, unsigned int, unsigned int);
	void NotifyShowHelp();
	void NotifyClearAll();
private:
	IObservable* mObservable;
};
