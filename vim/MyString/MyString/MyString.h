#pragma once

#ifndef _MYSTRING_H
#define _MYSTRING_H

#include <string>

class MyString {
public:
    MyString();
    MyString(const MyString& to_copy);
    explicit MyString(const char* array);
    explicit MyString(const std::string& string);
    MyString(const char* array, size_t count);
    MyString(size_t count, char character);

    ~MyString();

    MyString operator +(const MyString& second) const;
    MyString operator +(char* second) const;
    MyString operator +(const std::string& second) const;

    MyString operator +=(const char* second);
    MyString operator +=(const std::string& second);
    MyString operator +=(const MyString& second);

    MyString& operator =(const char* second);
    MyString& operator =(const std::string& second);
    MyString& operator =(const char second);
    MyString& operator =(const MyString& second);

    char operator [](size_t index) const;

    bool operator >(const MyString& second) const;
    bool operator <(const MyString& second) const;
    bool operator >=(const MyString& second) const;
    bool operator <=(const MyString& second) const;
    bool operator ==(const MyString& second) const;
    bool operator !=(const MyString& second) const;

    char* c_str() const;
    char* data() const;
    size_t length() const;
    size_t size() const;
    bool empty() const;
    size_t capacity() const;
    void shrink_to_fit();
    void clear();

    friend std::ostream& operator<<(std::ostream& out, MyString& string);
    friend std::istream& operator>>(std::istream& in, MyString& string);

    void insert(size_t index, size_t count, char character);
    void insert(size_t index, const char* string);
    void insert(size_t index, const char* string, size_t count);
    void insert(size_t index, const std::string& string);
    void insert(size_t index, std::string string, size_t count);

    void erase(size_t index, size_t count);

    void append(size_t count, char character);
    void append(const char* string);
    void append(const char* string, size_t index, size_t count);
    void append(const std::string& string);
    void append(const std::string& string, size_t index, size_t count);

    void replace(size_t index, size_t count, const char* string);
    void replace(size_t index, size_t count, const std::string& string);

    MyString substr(size_t index) const;
    MyString substr(size_t index, size_t count) const;

    int find(const char* string) const;
    int find(const char* string, size_t index) const;
    int find(const std::string& string) const;
    int find(const std::string& string, size_t index) const;

private:
    char* mString;
    size_t mCapacity;
    size_t mLength;

    int StrCmp(const char* str1, const char* str2) const;
    const char* StrStr(const char* string, const char* substring) const;
};


#endif //_MYSTRING_H