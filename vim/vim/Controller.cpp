#include "Controller.h"

Controller::Controller(Model* model)
{
	my_model = model;
}

void Controller::Input()
{
	while (true) 
	{
		auto c = _getch();
		
		if (c == Globals::Keyboard::ESCAPE) 
		{
			break;
		}
		
		if (c == Globals::Keyboard::FUNCTIONAL_KEYS) 
		{
			c = _getch();
		}
		
		my_model->InputKeyboard(c);
		
		ShowStatusBar();
		
		my_model->SetFlagChange(true);
	}
}

void Controller::ShowStatusBar()
{
	MyString mode("Insert");
	
	my_model->NotifyShowStatusBar(mode, my_model->GetFileName(), my_model->GetY() + 1, my_model->GetSizeText());
	my_model->NotifySetCursor(my_model->GetX(), my_model->GetY() - my_model->GetUpVisible());
}

void Controller::Command(int code)
{
	MyString mode("Command");
	
	my_model->NotifyShowStatusBar(mode, my_model->GetFileName(), my_model->GetY() + 1, my_model->GetSizeText());
	
	MyString command;
	
	size_t size = 1;
	auto c = 0;
	
	my_model->NotifyClearForCommand(50, 80);
	my_model->NotifyPrepareForCommand();
	my_model->NotifyShowInput(':');
	
	while (c != Globals::Keyboard::ENTER) 
	{
		auto c = _getch();
		
		if (c == Globals::Keyboard::ESCAPE)
		{
			command.clear(); break;
		}
		
		if (c == Globals::Keyboard::ENTER)
		{
			break;
		}
		
		auto tem = static_cast<char>(c);
		
		my_model->NotifyShowInput(tem);
		
		command.append(size, tem);
	}
	
	my_model->NotifyClearForCommand(50, 80);
	my_model->CheckUpdate();
	my_model->CheckUpdate();
	
	size_t y = 0;
	
	if (command.empty())
	{
		return;
	}
	
	if (command[y] == 'h' && command.size() == 1) 
	{
		size_t zam_one;
		size_t zam_two;
		
		zam_one = my_model->GetUpVisible();
		zam_two = my_model->GetDownVisible();
		
		my_model->NotifyShowHelp();
		
		c = _getch();
		
		my_model->NotifyClearAll();
		
		if (my_model->GetText().empty())
		{
			return;
		}
		
		my_model->NotifyUpdateScrolling(zam_one, zam_two, my_model->GetText());
		
		return;
	}
	
	auto flag = true;
	size_t num = 0;
	
	for (size_t i = 0; i < command.size(); i++) {
		
		if (command[i] >= '0' && command[i] <= '9') 
		{
			num *= 10;
			num += command[i] - '0';
		}
		else 
		{
			flag = false;
		}
	}
	
	if (flag)
	{
		my_model->GetNumberOfLine(num); return;
	}
	
	if (command[y] == 'o') 
	{
		size_t start = 0;
		size_t col = 2;
		
		command.erase(start, col);
		
		MyString file_name(command);
		my_model->OpenFile(file_name);
		
		return;
	}
	
	if (command[y] == 'x' && command.size() == 1) 
	{
		my_model->WriteFile();
		mEndFlag = true;
		
		return;
	}
	
	if (command[y] == 'w' && command.size() == 1) {
		
		my_model->WriteFile();
		
		return;
	}
	
	if (command[y] == 'q' && command.size() == 1) 
	{
		if (!my_model->GetFlagChange()) 
		{
			mEndFlag = true;
		}
		
		return;
	}
	
	if (command[y] == 'q' && command[size] == '!' && command.size() == 2) 
	{
		mEndFlag = true;
		return;
	}
	
	auto zam_size = size + 1;
	
	if (command[y] == 'w' && command[size] == 'q' &&
		command[zam_size] == '!' && command.size() == 3) 
	{
		my_model->SetFlagChange(false);
		my_model->WriteFile();
		
		mEndFlag = true;
		
		return;
	}
	
	if (command[y] == 'w') 
	{
		unsigned int start = 0;
		unsigned int col = 2;
		
		command.erase(start, col);
		
		MyString file_name(command);
		my_model->SetFlagChange(false);
		my_model->WriteFile(file_name);
		
		return;
	}
}

void Controller::Insert(int code)
{
	ShowStatusBar();
	
	if (code == Globals::Keyboard::KEY_I) 
	{
		Input();
		return;
	}
	
	if (code == Globals::Keyboard::PAGE_UP || code == Globals::Keyboard::KEY_S || code == Globals::Keyboard::KEY_A) 
	{
		my_model->SetX(code);
		Input();
		return;
	}
	
	if (code == Globals::Keyboard::KEY_R) 
	{
		my_model->DeleteSymbol();
		my_model->InsertCopy();
		return;
	}
}

void Controller::NavigationAndEditing(int code)
{
	while (true) 
	{
		MyString mode("Navigation");
		my_model->NotifyShowStatusBar(mode, my_model->GetFileName(), my_model->GetY() + 1, my_model->GetSizeText());
		my_model->NotifySetCursor(my_model->GetX(), my_model->GetY() - my_model->GetUpVisible());
		
		auto c = _getch();
		
		if (c == Globals::Keyboard::FUNCTIONAL_KEYS) 
		{
			c = _getch();
			
			if (c == Globals::Keyboard::PAGE_UP || c == Globals::Keyboard::PAGE_DOWN) 
			{
				my_model->PgUpDown(c);
			}
			else
			{
				my_model->ArrowsNavigation(c);
			}
			
			continue;
		}
		
		if (c == Globals::Keyboard::KEY_AMPERSAND || c == Globals::Keyboard::KEY_DOLLAR) 
		{
			my_model->StartEnd(c);
			
			continue;
		}
		
		if (c == Globals::Keyboard::KEY_P) 
		{
			my_model->InsertCopy();
			
			continue;
		}
		
		if (c == Globals::Keyboard::KEY_Y) 
		{
			my_model->CopyLine();
			
			c = _getch();
			
			if (c == Globals::Keyboard::KEY_W) 
			{
				my_model->CopyWord();
			}
			
			continue;
		}
		
		if (c == Globals::Keyboard::KEY_D) 
		{
			c = _getch();
			
			if (c == Globals::Keyboard::KEY_D) 
			{
				my_model->DeleteLine();
			}
			
			if (c == Globals::Keyboard::KEY_I) 
			{
				c = _getch();
				
				if (c == Globals::Keyboard::KEY_W) 
				{
					my_model->DeleteWord();
				}
			}
			
			continue;
		}
		
		if (c == Globals::Keyboard::KEY_X) 
		{
			my_model->DeleteSymbol();
			
			continue;
		}
		
		if (c == Globals::Keyboard::KEY_G_UPPER) 
		{
			my_model->GetEndOfFile();
			
			continue;
		}
		
		if (c >= '0' && c <= '9') 
		{
			size_t num = c - '0';
			
			while (true) 
			{
				c = _getch();
				
				if (c == Globals::Keyboard::KEY_G_UPPER) 
				{
					my_model->GetNumberOfLine(num);
					
					break;
				}
				else 
				{
					if (c >= '0' && c <= '9') 
					{
						num *= 10;
						num += c - '0';
					}
					else 
					{
						break;
					}
				}
			}
			
			continue;
		}
		
		if (c == Globals::Keyboard::KEY_G_LOWER) 
		{
			c = _getch();
			
			if (c == Globals::Keyboard::KEY_G_LOWER) 
			{
				my_model->GetFileBeginning();
				
				continue;
			}
		}
		
		if (c == Globals::Keyboard::KEY_W || c == Globals::Keyboard::KEY_B) 
		{
			my_model->StartEndOfWord(c);
			
			continue;
		}
		
		if (c == Globals::Keyboard::SLASH || 
			c == Globals::Keyboard::QUESTION_MARK || 
			c == Globals::Keyboard::KEY_N_UPPER || 
			c == Globals::Keyboard::KEY_N_LOWER) 
		{
			Search(c);
			continue;
		}
		
		if (c == Globals::Keyboard::KEY_I || 
			c == Globals::Keyboard::PAGE_UP || 
			c == Globals::Keyboard::KEY_A || 
			c == Globals::Keyboard::KEY_S || 
			c == Globals::Keyboard::KEY_R) 
		{
			Insert(c);
			continue;
		}
		
		if (c == Globals::Keyboard::COLON) 
		{
			Command(0);
			
			if (mEndFlag)
			{
				return;
			}
		}
	}
}

void Controller::Search(int code)
{
	MyString  mode("Search");
	my_model->NotifyShowStatusBar(mode, my_model->GetFileName(), my_model->GetY() + 1, my_model->GetSizeText());
	my_model->NotifySetCursor(my_model->GetX(), my_model->GetY() - my_model->GetUpVisible());
	
	if (code == Globals::Keyboard::SLASH || code == Globals::Keyboard::QUESTION_MARK) 
	{
		auto flag = 1;
		
		my_model->NotifyClearForCommand(50, 80);
		my_model->NotifyPrepareForCommand();
		
		if (code == Globals::Keyboard::SLASH) 
		{
			my_model->NotifyShowInput('/');
		}
		
		if (code == Globals::Keyboard::QUESTION_MARK) 
		{
			flag = -1;
			my_model->NotifyShowInput('?');
		}
		
		MyString temp;
		size_t size = 1;
		auto c = 'a';
		
		while (c != Globals::Keyboard::ENTER) 
		{
			c = _getch();
			
			if (c == Globals::Keyboard::ENTER) 
			{
				break;
			}
			
			if (c == Globals::Keyboard::ESCAPE) 
			{
				temp.clear();
				break;
			}
			
			auto tem = static_cast<char>(c);
			
			my_model->NotifyShowInput(tem);
			temp.append(size, tem);
		}
		
		my_model->NotifyClearForCommand(50, 80);
		my_model->GetWord(flag, temp);
		
		return;
	}
	
	if (code == Globals::Keyboard::KEY_N_UPPER) 
	{
		if (!my_model->GetFinded().empty()) 
		{
			my_model->FindWord(1);
		}
		
		return;
	}
	
	if (code == Globals::Keyboard::KEY_N_LOWER)
	{
		if (!my_model->GetFinded().empty()) 
		{
			my_model->FindWord(-1);
		}
	}
}
