#include "Model.h"

Model::Model() : x{ 0 }, y{ 0 }, visible_up{ 0 }, visible_down{ 0 } {}

void Model::ArrowsNavigation(int code)
{
	if (code == Globals::Keyboard::ARROW_UP) 
	{
		if (y > 0) 
		{
			--y;
			
			if (!my_text.at(y).empty()) 
			{
				x = my_text.at(y).size() - 1 >= x ? x : my_text.at(y).size() - 1;
			}
			else 
			{
				x = 0;
			}
			
			CheckUpdate();
		}
	}
	else 
	{
		if (code == Globals::Keyboard::ARROW_DOWN) 
		{
			if (my_text.empty() || y == my_text.size() - 1)
			{
				return;
			}
			else 
			{
				++y;
				
				if (my_text.at(y).empty()) 
				{
					x = 0;
				}
				else
				{
					x = my_text.at(y).size() - 1 < x ? my_text.at(y).size() - 1 : x;
				}
				
				CheckUpdate();
			}
		}
		else 
		{
			if (code == Globals::Keyboard::ARROW_LEFT) 
			{
				if (x > 0)
				{
					--x;
				}
				
				NotifySetCursor(x, y - visible_up);
			}
			else 
			{
				if (code == Globals::Keyboard::ARROW_RIGHT) 
				{
					size_t temp = 0;
					
					if (!my_text.empty()) 
					{
						temp = GetRealSize();
					}
					
					if (x < temp) 
					{
						++x;
						
						NotifySetCursor(x, y - visible_up);
					}
				}
			}
		}
	}
}

void Model::StartEnd(int code)
{
	
	if (code == Globals::Keyboard::KEY_AMPERSAND) 
	{
		SetX(Globals::Keyboard::PAGE_UP);
	}
	else 
	{
		if (code == Globals::Keyboard::KEY_DOLLAR) 
		{
			SetX(Globals::Keyboard::KEY_A);
		}
	}
}

void Model::StartEndOfWord(int code)
{
	unsigned int zam_x = x, zam_y = y;
	
	if (my_text.at(y)[x] == '\n' || my_text.at(y)[x] == ' ')
	{
		return;
	}
	
	if (code == Globals::Keyboard::KEY_W) 
	{
		for (auto i = y; i < my_text.size(); i++) 
		{
			for (auto j = x; j < my_text.at(i).size(); j++) 
			{
				if (my_text.at(i)[j] == ' ' || my_text.at(i)[j] == '\n') 
				{
					y = i; x = j;
					
					CheckUpdate();

					return;
				}
			}
			
			x = 0;
		}
		
		SetX(Globals::Keyboard::KEY_A);
	}
	
	if (code == Globals::Keyboard::KEY_B) 
	{
		for (int i = y; i >= 0;) 
		{
			for (int j = x; j >= 0; j--) 
			{
				unsigned int zam_j = j;
				
				if (my_text.at(i)[zam_j] == ' ') 
				{
					y = i;
					x = zam_j + 1;
					
					if (x == Globals::Window::HORIZONTAL)
					{
						x = 0;
						y = i + 1;
					}
					
					CheckUpdate();

					return;
				}
				
				if (my_text.at(i)[zam_j] == '\n') 
				{
					y = i + 1;
					x = 0;
					
					CheckUpdate();

					return;
				}
			}
			
			i--;
			
			if (i >= 0)
			{
				x = !my_text.at(i).empty() ? my_text.at(i).size() - 1 : 0;
			}
			else
			{
				break;
			}
		}
		
		SetX(Globals::Keyboard::PAGE_UP);
	}
}

void Model::GetFileBeginning()
{
	x = 0;
	y = 0;
	
	visible_up = 0;
	visible_down = my_text.size() >= Globals::Window::VERTICAL - 1 ? Globals::Window::VERTICAL - 1 : my_text.size();
	
	NotifyUpdateScrolling(visible_up, visible_down, my_text);
	NotifySetCursor(x, y);
}

void Model::GetNumberOfLine(unsigned int num)
{
	if (num > my_text.size() && num > 0 || num == 0) 
	{
		return;
	}
	else 
	{
		y = num - 1;
		x = 0;
		
		CheckUpdate();
	}
}

void Model::InsertCopy()
{
	MyString final_str("");
	MyString my_str("");
	
	if (!copy.empty()) 
	{
		auto zam_x = x;
		auto zam_y = y;
		
		size_t one = 1;
		auto temp = x;
		
		SetX(Globals::Keyboard::PAGE_UP);
		SetX(Globals::Keyboard::KEY_A);
		
		auto local_up = y;
		auto local_down = y;
		
		x = zam_x;
		y = zam_y;
		
		my_str.append(my_text.at(zam_y).c_str());
		my_str.insert(x, copy.c_str());
		
		for (unsigned int i = local_up; i < zam_y; i++) 
		{
			final_str.append(my_text.at(i).c_str());
		}
		
		for (unsigned int i = zam_y + 1; i <= local_down; i++) 
		{
			my_str.append(my_text.at(i).c_str());
		}
		
		final_str.append(my_str.c_str());
		
		temp = final_str.size() - 1;
		
		if (final_str[temp] == '\n')
		{
			final_str.erase(temp, one);
		}
		
		SetX(Globals::Keyboard::KEY_S);
		
		my_text.erase(my_text.begin() + y);
		
		HorizontalScrolling(final_str);
		
		x = zam_x;
		y = zam_y;
		
		CheckUpdate();
	}
}

void Model::GetEndOfFile()
{
	y = !my_text.empty() >= 1 ? my_text.size() - 1 : 0;
	x = !my_text.at(y).empty() >= 1 ? my_text.at(y).size() - 1 : 0;
	
	CheckUpdate();
}

void Model::PgUpDown(int code)
{
	DetermineVisionLine();
	
	if (code == Globals::Keyboard::PAGE_UP) 
	{
		if (visible_up >= Globals::Window::VERTICAL - 1)
		{
			visible_down = visible_up;
			visible_up -= Globals::Window::VERTICAL - 1;
			y = visible_up;
		}
		else 
		{
			y = 0;
		}
	}
	else 
	{
		if (visible_down + Globals::Window::VERTICAL < my_text.size())
		{
			visible_up = visible_down;
			visible_down += Globals::Window::VERTICAL - 1;
		}
		else 
		{
			visible_down = my_text.size() - 1;
			
			if (visible_down >= Globals::Window::VERTICAL - 1)
			{
				visible_up = visible_down - Globals::Window::VERTICAL - 1;
			}
			else { visible_up = 0; }
		}
		
		y = visible_down;
	}
	
	x = 0;
	
	CheckUpdate();
}

void Model::DeleteSymbol()
{
	auto zam_x = x;
	auto zam_y = y;
	
	size_t one = 1;
	auto temp = x;

	SetX(Globals::Keyboard::PAGE_UP);
	SetX(Globals::Keyboard::KEY_A);
	
	auto local_up = y;
	auto local_down = y;
	
	x = zam_x;
	y = zam_y;
	
	MyString local_str("");

	auto flag = true;

	if (my_text.at(zam_y)[x] == '\0' || my_text.at(zam_y)[x] == '\n')
	{
		flag = false;
	}
	
	if (!flag) 
	{
		return;
	}

	for (auto i = local_up; i <= local_down; i++) 
	{
		if (i == zam_y) 
		{
			my_text.at(i).erase(temp, one);
		}
		
		local_str.append(my_text.at(i).c_str());
	}
	
	temp = local_str.size() - 1;
	local_str.erase(temp, one);
	
	x = zam_x;
	y = zam_y;
	
	SetX(Globals::Keyboard::KEY_S);
	
	my_text.erase(my_text.begin() + y);
	
	HorizontalScrolling(local_str);
	
	x = zam_x;
	y = zam_y;
	
	CheckUpdate();
}

void Model::DeleteWord()
{
	StartEndOfWord(Globals::Keyboard::KEY_B);
	
	while (my_text.at(y)[x] != ' ' && my_text.at(y)[x] != '\n') 
	{
		DeleteSymbol();
	}
	
	DeleteSymbol();
}

void Model::CopyLine()
{
	copy.clear();
	
	auto zam_x = x;
	auto zam_y = y;
	
	size_t one = 1;
	auto temp = x;
	
	SetX(Globals::Keyboard::PAGE_UP);
	SetX(Globals::Keyboard::KEY_A);

	unsigned int local_up = y;
	unsigned int local_down = y;
	
	x = zam_x;
	y = zam_y;
	
	CheckUpdate();
	
	MyString local_str("");
	
	for (auto i = local_up; i <= local_down; i++) 
	{
		local_str.append(my_text.at(i).c_str());
	}
	
	temp = local_str.size() - 1;
	local_str.erase(temp, one);
	
	copy.append(local_str.c_str());
}

void Model::CopyWord()
{
	copy.clear();
	
	StartEndOfWord(Globals::Keyboard::KEY_B);
	
	unsigned int one = 1;
	auto zam_x = x;
	auto zam_y = y;
	
	while (my_text.at(zam_y)[zam_x] != ' ' && my_text.at(zam_y)[zam_x] != '\n') 
	{
		auto t = my_text.at(zam_y)[zam_x];
		
		if (zam_x == Globals::Window::HORIZONTAL - 1)
		{
			++zam_y;
			zam_x = 0;
		}
		
		++zam_x;
		
		copy.append(one, t);
	}
}

void Model::DeleteLine()
{
	if (my_text.empty())
	{
		return;
	}
	
	SetX(Globals::Keyboard::KEY_S);
	
	my_text.erase(my_text.begin() + y);
	
	if (y > 0)
	{
		--y;
	}
	
	if (visible_down > my_text.size()) 
	{
		visible_down = !my_text.empty() ? my_text.size() - 1 : 0;
		
		if (visible_down >= Globals::Window::VERTICAL - 1) 
		{
			visible_up = visible_down - Globals::Window::VERTICAL - 1;
		}
		else
		{
			visible_up = 0;
		}
	}
	
	CheckUpdate();
}

void Model::InputKeyboard(int code)
{
	size_t one = 1;
	
	MyString new_line("");
	MyString part("");
	
	auto q = '\n';
	
	if (code == Globals::Keyboard::BACKSPACE) 
	{
		DeleteSymbol();
		return;
	}
	
	if (code == Globals::Keyboard::ARROW_RIGHT || 
		code == Globals::Keyboard::ARROW_DOWN || 
		code == Globals::Keyboard::ARROW_UP || 
		code == Globals::Keyboard::ARROW_LEFT) 
	{
		ArrowsNavigation(code);
		return;
	}
	
	if (code == Globals::Keyboard::ENTER) 
	{
		if (!my_text.empty()) 
		{
			my_text.at(y).insert(x, one, q);
			
			x += 1;

			size_t col_num = 0;
			
			for (auto i = x; i < my_text.at(y).size(); i++) 
			{
				part.append(one, my_text.at(y)[i]);
				
				++col_num;
			}
			
			my_text.at(y).erase(x, col_num);
			
			NotifyUpdateLine(y - visible_up, my_text.at(y));
			
			++y;
			x = 0;
			
			my_text.insert(my_text.begin() + y, new_line);
			my_text.at(y).append(part.c_str());
			
			CheckUpdate();
		}
		else 
		{
			my_text.push_back(new_line);
			my_text.at(0).append(one, q);
			my_text.push_back(new_line);
			
			x = 0;
			y += 1;
		}
	}
	else 
	{
		auto temp = static_cast<char>(code);
		char mas[2] = { 0 };
		
		mas[0] = temp;
		mas[1] = '\0';
		
		if (!my_text.empty()) 
		{
			MyString temp_copy(copy);
			
			copy.clear();
			copy.append(mas);
			
			auto zam_x = x;
			auto zam_y = y;
			
			InsertCopy();
			
			++zam_x;
			
			if (zam_x > 80) 
			{
				x = 1;
				y = zam_y + 1;
			}
			else 
			{
				x = zam_x;
			}
		}
		else 
		{
			my_text.push_back(new_line);
			my_text.at(0).append(one, temp);
			
			visible_up = visible_down = 0;
			
			y = 0;
			x = GetRealSize() + 1;
		}
	}
	
	CheckUpdate();
}

void Model::GetWord(int direct, MyString rez)
{
	find = rez;
	
	if (find.empty()) 
	{
		return;
	}
	
	FindWord(direct);
}

void Model::FindWord(int direct)
{
	MyString sum_str("");
	
	if (direct > 0) 
	{
		auto zam_y = y;
		
		SetX(Globals::Keyboard::KEY_A);
		
		x = 0;
		
		for (auto i = y + 1; i < my_text.size(); i++) 
		{
			sum_str.append(my_text.at(i).c_str());
			
			if (sum_str.find(find.c_str()) != -1) 
			{
				x = 0;
				y = i;
				
				SetX(Globals::Keyboard::PAGE_UP);
				
				return;
			}
		}
		
		y = zam_y;
	}
	else 
	{
		SetX(Globals::Keyboard::PAGE_UP);
		
		for (int i = y - 1; i >= 0; i--) 
		{
			unsigned int start = 0;

			sum_str.insert(start, my_text.at(i).c_str());
			
			if (sum_str.find(find.c_str()) != -1) 
			{
				x = 0;
				y = i;
				
				SetX(73);
				
				return;
			}
		}
	}
	
	x = 0;
	
	CheckUpdate();
}

void Model::WriteFile()
{
	if (file_name.empty())
	{
		return;
	}
	
	std::ofstream fout(file_name.c_str());

	for (auto i : my_text)
	{
		fout << i;
	}

	fout.close();
}

void Model::SetX(unsigned int x)
{
	if (my_text.empty())
	{
		return;
	}
	
	if (x == Globals::Keyboard::KEY_A) 
	{
		while (true) 
		{
			auto my_size = GetRealSize();
			
			if (my_text.at(y)[my_size] == '\n') 
			{
				break;
			}
			
			++y;
			
			if (y >= my_text.size()) 
			{
				--y;
				
				break;
			}
		}
		
		this->x = GetRealSize() >= 0 ? GetRealSize() + 1 : 0;
		this->x = this->x >= 1 ? this->x - 1 : 0;
	}
	else 
	{
		SetX(Globals::Keyboard::KEY_A);
		
		auto zam_y = y;
		
		if (y > 0) 
		{
			while (true) 
			{
				if (y > 0)
				{
					--y;
				}
				
				auto my_size = GetRealSize();
				
				if (my_text.at(y)[my_size] == '\n') 
				{
					++y;
					
					break;
				}
				
				if (y == 0) 
				{
					break;
				}
			}
		}
		
		this->x = 0;
		
		if (x != Globals::Keyboard::PAGE_UP)
		{
			for (auto i = y; i < zam_y; i++) 
			{
				my_text.erase(my_text.begin() + y);
			}
			
			my_text.at(y).clear();
			
			unsigned int col = 1;
			auto tr = '\n';
			
			my_text.at(y).append(col, tr);
		}
	}
	
	CheckUpdate();
}

void Model::OpenFile(MyString name)
{
	x = 0;
	y = 0;
	
	std::ifstream fin(name.c_str());
	
	if (!fin.is_open()) 
	{
		return;
	}
	
	my_text.clear();
	
	NotifyClearAll();
	NotifySetCursor(0, 0);
	
	file_name = name;
	
	while (fin) 
	{
		std::string str;
		std::getline(fin, str);
		MyString string(str);
		
		HorizontalScrolling(string);
	}
	
	fin.close();
	
	GetFileBeginning();
}

void Model::WriteFile(MyString str)
{
	if (str.empty())
	{
		return;
	}
	
	std::ofstream fout(str.c_str());
	
	auto zam_x = x;
	auto zam_y = y;
	
	NotifyPrepareForCommand();
	
	if (!fout) 
	{
		NotifyShowInput('!');
		NotifyShowInput('o');
		NotifyShowInput('k');
		
		x = zam_x;
		y = zam_y;
		
		return;
	}
	else 
	{
		NotifyShowInput('o');
		NotifyShowInput('k');
	}
	
	x = zam_x;
	y = zam_y;

	for (auto i : my_text)
	{
		fout << i;
	}
	
	fout.close();
}

bool Model::IsPathExist(MyString& str)
{
	struct stat buffer;
	return (stat(str.c_str(), &buffer) == 0);
}

void Model::HorizontalScrolling(MyString str)
{
	unsigned int col = 1;
	auto tre = '\n';
	
	if (str.size() < Globals::Window::HORIZONTAL + 1) 
	{
		my_text.insert(my_text.begin() + y, str);
		my_text.at(y).append(col, tre);
		
		++y;
	}
	else 
	{
		MyString temp_str;
		
		for (unsigned int i = 0; i < str.size(); i++) 
		{
			temp_str.append(col, str[i]);
			
			if (temp_str.size() == Globals::Window::HORIZONTAL && str.size() - 1 != i)
			{
				my_text.insert(my_text.begin() + y, temp_str);
				
				++y;

				temp_str.clear();
			}
			
			if (str.size() - 1 == i && temp_str.size() == Globals::Window::HORIZONTAL)
			{
				my_text.insert(my_text.begin() + y, temp_str);
				
				++y;

				temp_str.clear();
				temp_str.append(col, tre);
				
				my_text.insert(my_text.begin() + y, temp_str);

				++y;
				
				break;
			}
			
			if (str.size() - 1 == i && temp_str.size() != Globals::Window::HORIZONTAL)
			{
				temp_str.append(col, tre);
				
				my_text.insert(my_text.begin() + y, temp_str);
				
				++y;
				
				break;
			}
		}
	}
}

unsigned int Model::GetRealSize()
{
	return !my_text.at(y).empty() ? my_text.at(y).size() - 1 : 0;
}

bool Model::DetermineVisionLine()
{
	if (visible_down < Globals::Window::VERTICAL - 1)
	{
		if (visible_down < my_text.size()) 
		{
			if (my_text.size() >= Globals::Window::VERTICAL - 1)
			{
				visible_down = Globals::Window::VERTICAL - 1;
			}
			else 
			{
				visible_down = my_text.size();
			}
			visible_up = 0;
		}
	}
	
	if (visible_down > my_text.size()) 
	{
		NotifyClearAll();
		
		visible_down = my_text.size();
		
		if (visible_down >= Globals::Window::VERTICAL - 1)
		{
			visible_up = visible_down - Globals::Window::VERTICAL - 1;
		}
		else
		{
			visible_up = 0;
		}
	}
	
	if (y >= visible_down) 
	{
		visible_down = y + 1;
		
		if (y >= Globals::Window::VERTICAL - 1)
		{
			visible_up = visible_down - Globals::Window::VERTICAL - 1;
		}
		else
		{
			visible_up = 0;
		}
		
		return true;
	}
	else 
	{
		if (y < visible_up) 
		{
			visible_up = y;
			visible_down = 
				y + Globals::Window::VERTICAL - 1 < my_text.size() ? y + Globals::Window::VERTICAL - 1 : my_text.size();
			
			return true;
		}
	}
	
	return false;
}

void Model::CheckUpdate()
{
	DetermineVisionLine();
	NotifyUpdateScrolling(visible_up, visible_down, my_text);
	NotifySetCursor(x, y - visible_up);
}