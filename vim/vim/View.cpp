#include "View.h"

View::View(Model* model)
{
	Draw::Init();
	model->AddObserver(this);
}

void View::SetCursor(unsigned int x, unsigned int y)
{
	Draw::SetCursor(x, y);
}

void View::UpdateScrolling(unsigned int up, unsigned int down, std::vector<MyString>& my_text)
{
	SetCursor(0, 0);
	
	if (my_text.empty())
	{
		return;
	}
	
	for (int i = up; i < down; i++) 
	{
		auto index = !my_text.at(i).empty() ? my_text.at(i).size() - 1 : 0;
		
		if (my_text.at(i)[index] == '\n')
		{
			std::cout << "\33[2K" << my_text.at(i);
		}
		else
		{
			std::cout << "\33[2K" << my_text.at(i) << std::endl;
		}
	}
}

void View::UpdateLine(unsigned int y, MyString string)
{
	SetCursor(0, y);
	
	std::cout << "\33[2K" << string;
}

void View::PrepareForCommand()
{
	SetCursor(50, Globals::Window::VERTICAL - 1);
}

void View::ClearForCommand(unsigned int start, unsigned int end)
{
	for (int i = start; i < end; i++) 
	{
		SetCursor(i, Globals::Window::VERTICAL - 1);
		
		std::cout << " ";
	}
}

void View::ShowInput(char string)
{
	std::cout << string;
}

void View::ShowStatusBar(MyString mode, MyString file, unsigned int cur, unsigned int all)
{
	ClearForCommand(0, Globals::Window::HORIZONTAL - 60);
	SetCursor(0, Globals::Window::VERTICAL - 1);
	
	std::cout << mode;
	
	SetCursor(12, Globals::Window::VERTICAL - 1);
	
	unsigned int index = 0;
	
	for (unsigned int i = 0; i < file.size(); i++) 
	{
		
		if (file[i] == '\\') 
		{
			index = i;
		}
	}
	
	auto i = index == 0 ? 0 : index + 1;
	
	for (; i < file.size(); i++) 
	{
		std::cout << file[i];
	}
	
	SetCursor(30, Globals::Window::VERTICAL - 1);
	
	std::cout << cur << "/" << all;
}

void View::ShowHelp()
{
	ClearAll();
	
	SetCursor(0, 0);
	
	std::cout << "Navigation and Edit mode:" << std::endl;
	std::cout << "Arrows - change cursor position;" << std::endl;
	std::cout << "^ - string beginning, $ - string end" << std::endl;
	std::cout << "w - end of the word; b - start of the word; gg - start file; G - end file" << std::endl;
	std::cout << "NG - n line; PG_UP PG_DOWN - screen up down; x - delete symbol after cur" << std::endl;
	std::cout << "diw - delete word under cur; dd - erase line; yy - copy line" << std::endl;
	std::cout << "yw - copy word under cur; p - insert after cur;" << std::endl;
	std::cout << std::endl;
	std::cout << "Search mode:" << std::endl;
	std::cout << "/<text> - find text after cur; ?<text> - find text before cur" << std::endl;
	std::cout << "n - repeat search; N - repeat reverse search" << std::endl;
	std::cout << std::endl;
	std::cout << "Insert mode:" << std::endl;
	std::cout << "i - insert text before cur; I - begin insert from start line" << std::endl;
	std::cout << "A - begin insert from end line; S - delete line and start insert" << std::endl;
	std::cout << "r - change one symbol under cursor" << std::endl;
	std::cout << std::endl;
	std::cout << "Command mode:" << std::endl;
	std::cout << "o filename - open file with filename; x - write cur file and exit" << std::endl;
	std::cout << "w - write cur file; w filename - write file with filename" << std::endl;
	std::cout << "q - quit without change; q! - quit without save; num - num line" << std::endl;
	std::cout << "h - help; wq! - write cur file and quit" << std::endl;
	std::cout << std::endl;
	std::cout << "Press any key..." << std::endl;
	
	SetCursor(16, 23);
}

void View::ClearAll()
{
	for (auto i = 0; i <= Globals::Window::VERTICAL - 2; i++) {
		
		SetCursor(0, i);
		
		std::cout << "\33[2K";
	}
}

