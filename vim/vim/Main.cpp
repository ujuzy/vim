#include <iostream>

#include "Model.h"
#include "View.h"
#include "Controller.h"

int main()
{
	Model model;
	View view(&model);
	Controller controller(&model);
	controller.NavigationAndEditing(1);
	
	return 0;
}