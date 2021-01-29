#include "Observer.h"

void Observer::AddObserver(IObservable* observer) {
	this->mObservable = observer;
}

void Observer::NotifySetCursor(unsigned int x, unsigned int y)
{
	mObservable->SetCursor(x, y);
}

void Observer::NotifyUpdateScrolling(unsigned int up, unsigned int down, std::vector<MyString>& my_text)
{
	mObservable->UpdateScrolling(up, down, my_text);
}

void Observer::NotifyUpdateLine(unsigned int y, MyString string)
{
	mObservable->UpdateLine(y, string);
}

void Observer::NotifyPrepareForCommand()
{
	mObservable->PrepareForCommand();
}

void Observer::NotifyClearForCommand(unsigned int start, unsigned int end)
{
	mObservable->ClearForCommand(start, end);
}

void Observer::NotifyShowInput(char symbol)
{
	mObservable->ShowInput(symbol);
}

void Observer::NotifyShowStatusBar(MyString mode, MyString file_name, unsigned int cur, unsigned int all)
{
	mObservable->ShowStatusBar(mode, file_name, cur, all);
}

void Observer::NotifyShowHelp()
{
	mObservable->ShowHelp();
}

void Observer::NotifyClearAll()
{
	mObservable->ClearAll();
}
