#pragma once

#include "Model.h"
#include <conio.h>

class Controller
{
public:
	Controller(Model* model);

	void Search(int code);
	void NavigationAndEditing(int code);
	void Insert(int code);
	void Command(int code);

	bool GetEndFlag() { return mEndFlag; }

private:
	void Input();
	void ShowStatusBar();

	Model* my_model;
	
	bool mEndFlag{ false };
};

