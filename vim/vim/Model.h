#pragma once

#include "Observer.h"
#include "Globals.h"
#include <fstream>

class Model : public Observer
{
public:
	Model();
	
	void ArrowsNavigation(int);
	void StartEnd(int);
	void StartEndOfWord(int);
	void GetFileBeginning();
	void GetNumberOfLine(unsigned int);
	void InsertCopy();
	void GetEndOfFile();
	void PgUpDown(int);
	void DeleteSymbol();
	void DeleteWord();
	void DeleteLine();
	void CopyLine();
	void CopyWord();
	void InputKeyboard(int code);
	void GetWord(int, MyString);
	void FindWord(int);
	void SetX(unsigned int);
	void OpenFile(MyString);
	void WriteFile();
	void WriteFile(MyString);
	void SetFlagChange(bool t) { flag_change = t; }
	void CheckUpdate();
	
	bool IsPathExist(MyString& str);
	bool GetFlagChange() { return flag_change; }
	
	unsigned int GetX() { return x; }
	unsigned int GetY() { return y; }
	unsigned int GetUpVisible() { return visible_up; }
	unsigned int GetDownVisible() { return visible_down; }
	unsigned int GetSizeText() { return my_text.size(); }
	
	std::vector<MyString>& GetText() { return my_text; }
	
	MyString GetFileName() { return file_name; }
	MyString GetFinded() { return find; }

private:
	void HorizontalScrolling(MyString);
	bool DetermineVisionLine();
	unsigned int GetRealSize();
	
	MyString file_name;
	MyString find;
	MyString copy;
	
	std::vector<MyString> my_text;
	
	unsigned int x, y;
	unsigned int visible_up, visible_down;
	
	bool flag_first_up = false;
	bool flag_change = false;
};

