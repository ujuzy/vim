// MyString.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"

#include <string>
#include <ostream>
#include <istream>

#include "MyString.h"

MyString::MyString() {
    this->mString = new char[1];
    mString[0] = 0;
    this->mCapacity = 1;
    this->mLength = 0;
}

MyString::MyString(const MyString& to_copy) {
    this->mString = new char[to_copy.length() + 1];

    for (size_t i = 0; i < to_copy.length() + 1; ++i) {
        this->mString[i] = to_copy[i];
    }

    this->mCapacity = to_copy.length() + 1;
    this->mLength = to_copy.length();
}

MyString::MyString(const char* array) {
    size_t length = 0;
    size_t i = 0;

    while (array[i++] != 0) {
        ++length;
    }

    this->mString = new char[length + 1];

    for (i = 0; i < length + 1; ++i) {
        this->mString[i] = array[i];
    }

    this->mCapacity = length + 1;
    this->mLength = length;
}

MyString::MyString(const char* array, size_t count) {
    this->mString = new char[count + 1];

    for (size_t i = 0; i < count; ++i) {
        this->mString[i] = array[i];
    }

    this->mString[count] = 0;

    this->mCapacity = count + 1;
    this->mLength = count;
}

MyString::MyString(size_t count, char character) {
    this->mString = new char[count + 1];

    for (size_t i = 0; i < count; ++i) {
        this->mString[i] = character;
    }

    this->mString[count] = 0;

    this->mCapacity = count + 1;
    this->mLength = count;
}

MyString::MyString(const std::string& string) {
    this->mString = new char[string.length() + 1];

    for (size_t i = 0; i < string.length(); ++i) {
        this->mString[i] = string[i];
    }

    this->mString[string.length()] = 0;

    this->mCapacity = string.length() + 1;
    this->mLength = string.length();
}

MyString::~MyString() {
    delete[] this->mString;
}

MyString MyString::operator+(const MyString& second) const {
    MyString new_string;

    new_string.mLength = this->mLength + second.mLength;
    new_string.mCapacity = new_string.mLength + 1;
    new_string.mString = new char[new_string.mCapacity]();
    new_string.mString[new_string.mLength] = 0;

    size_t i;

    for (i = 0; i < this->mLength; ++i) {
        new_string.mString[i] = this->mString[i];
    }

    for (size_t j = 0; j < second.mLength; ++j) {
        new_string.mString[i + j] = second.mString[j];
    }

    return new_string;
}

MyString MyString::operator+(char* second) const {
    size_t second_length = 0;
    size_t i = 0;

    while (second[i++] != 0) {
        ++second_length;
    }

    MyString new_string;

    new_string.mLength = this->mLength + second_length;
    new_string.mCapacity = new_string.mLength + 1;
    new_string.mString = new char[new_string.mCapacity]();
    new_string.mString[new_string.mLength] = 0;

    for (i = 0; i < this->mLength; ++i) {
        new_string.mString[i] = this->mString[i];
    }

    for (size_t j = 0; j < second_length; ++j) {
        new_string.mString[i + j] = second[j];
    }

    return new_string;
}

MyString MyString::operator+(const std::string& second) const {
    size_t i = 0;

    MyString new_string;

    new_string.mLength = this->mLength + second.length();
    new_string.mCapacity = new_string.mLength + 1;
    new_string.mString = new char[new_string.mCapacity]();
    new_string.mString[new_string.mLength] = 0;

    for (i = 0; i < this->mLength; ++i) {
        new_string.mString[i] = this->mString[i];
    }

    for (size_t j = 0; j < second.length(); ++j) {
        new_string.mString[i + j] = second[j];
    }

    return new_string;
}

MyString MyString::operator+=(const char* second) {
    size_t second_length = 0;
    size_t i = 0;

    while (second[i++] != 0) {
        ++second_length;
    }

    if (this->mCapacity - this->mLength > second_length) {
        for (i = 0; i < second_length; ++i) {
            this->mString[this->mLength + i] = second[i];
        }

        this->mLength += second_length;
    }
    else {
        auto tmp = new char[this->mLength + 1];

        for (i = 0; i < this->mLength; ++i) {
            tmp[i] = this->mString[i];
        }

        tmp[this->mLength] = 0;

        delete[] this->mString;
        this->mString = new char[this->mLength + second_length + 1];

        auto previous_length = this->mLength;
        this->mLength += second_length;
        this->mCapacity = this->mLength + 1;

        for (i = 0; i < previous_length; ++i) {
            this->mString[i] = tmp[i];
        }

        for (i = 0; i < second_length; ++i) {
            this->mString[previous_length + i] = second[i];
        }

        this->mString[this->mLength] = 0;

        delete[] tmp;
    }

    return *this;
}

MyString MyString::operator+=(const std::string& second) {
    size_t i = 0;

    if (this->mCapacity - this->mLength > second.length()) {
        for (i = 0; i < second.length(); ++i) {
            this->mString[this->mLength + i] = second[i];
        }

        this->mLength += second.length();
    }
    else {
        auto tmp = new char[this->mLength + 1];

        for (i = 0; i < this->mLength; ++i) {
            tmp[i] = this->mString[i];
        }

        tmp[this->mLength] = 0;

        delete[] this->mString;
        this->mString = new char[this->mLength + second.length() + 1];

        auto previous_length = this->mLength;
        this->mLength += second.length();
        this->mCapacity = this->mLength + 1;

        for (i = 0; i < previous_length; ++i) {
            this->mString[i] = tmp[i];
        }

        for (i = 0; i < second.length(); ++i) {
            this->mString[previous_length + i] = second[i];
        }

        this->mString[this->mLength] = 0;

        delete[] tmp;
    }

    return *this;
}

MyString MyString::operator +=(const MyString& second) {
    return *this += second.mString;
}

MyString& MyString::operator=(const char second) {
    if (this->mCapacity <= 1) {
        delete[] this->mString;
        this->mString = new char[2];
        this->mCapacity = 2;
    }

    this->mString[0] = second;
    this->mString[1] = 0;
    this->mLength = 1;

    return *this;
}

MyString& MyString::operator=(const char* second) {
    size_t second_length = 0;
    size_t i = 0;

    while (second[i++]) {
        ++second_length;
    }

    if (this->mCapacity > second_length) {
        for (i = 0; i < second_length; ++i) {
            this->mString[i] = second[i];
        }

        this->mLength = second_length;
    }
    else {
        delete[] this->mString;

        this->mString = new char[second_length + 1];
        this->mLength = second_length;
        this->mCapacity = second_length + 1;

        for (i = 0; i < second_length; ++i) {
            this->mString[i] = second[i];
        }
    }

    this->mString[second_length] = 0;

    return *this;
}

MyString& MyString::operator=(const std::string& second) {
    return *this = second.c_str();
}

MyString& MyString::operator=(const MyString& second) {
    return *this = second.mString;
}

char MyString::operator[](size_t index) const {
    return this->mString[index];
}

bool MyString::operator >(const MyString& second) const {
    if (StrCmp(this->mString, second.mString) > 0) {
        return true;
    }

    return false;
}

bool MyString::operator >=(const MyString& second) const {
    if (StrCmp(this->mString, second.mString) > 0 || StrCmp(this->mString, second.mString) == 0) {
        return true;
    }

    return false;
}

bool MyString::operator <(const MyString& second) const {
    if (StrCmp(this->mString, second.mString) < 0) {
        return true;
    }

    return false;
}

bool MyString::operator <=(const MyString& second) const {
    if (StrCmp(this->mString, second.mString) < 0 || StrCmp(this->mString, second.mString) == 0) {
        return true;
    }

    return false;
}

bool MyString::operator ==(const MyString& second) const {
    if (StrCmp(this->mString, second.mString) == 0)
    {
        return true;
    }

    return false;
}

bool MyString::operator !=(const MyString& second) const {
    if (StrCmp(this->mString, second.mString) != 0) {
        return true;
    }

    return false;
}

char* MyString::c_str() const {
    return this->mString;
}

char* MyString::data() const {
    return this->mString;
}

size_t MyString::capacity() const {
    return this->mCapacity;
}

size_t MyString::size() const {
    return this->mLength;
}

bool MyString::empty() const {
    if (this->mString[0] == 0) {
        return true;
    }

    return false;
}

void MyString::clear() {
    for (size_t i = 0; i < this->mLength; ++i) {
        this->mString[i] = 0;
    }

    this->mLength = 0;
}

void MyString::shrink_to_fit() {
    auto tmp = new char[this->mLength + 1];

    for (size_t i = 0; i < this->mLength + 1; ++i) {
        tmp[i] = this->mString[i];
    }

    delete[] this->mString;

    this->mString = new char[this->mLength + 1];
    this->mCapacity = this->mLength + 1;

    for (size_t i = 0; i < this->mLength + 1; ++i) {
        this->mString[i] = tmp[i];
    }

    this->mCapacity = this->mLength + 1;

    delete[] tmp;
}

size_t MyString::length() const {
    return this->mLength;
}

void MyString::insert(size_t index, size_t count, char character) {
    if (this->mCapacity - this->mLength > count) {
        auto temp = new char[this->mLength - index];

        for (size_t i = index; i < this->mLength; ++i) {
            temp[i - index] = this->mString[i];
        }

        for (size_t i = index; i < index + count; ++i) {
            this->mString[i] = character;
        }

        this->mLength += count;

        for (size_t i = 0; i < this->mLength - index; ++i) {
            this->mString[i + index + count] = temp[i];
        }

        this->mString[this->mLength] = 0;

        delete[] temp;
    }
    else {
        auto temp = new char[this->mLength + count + 1];

        for (size_t i = 0; i < index; ++i) {
            temp[i] = this->mString[i];
        }

        for (auto i = index; i < index + count; ++i) {
            temp[i] = character;
        }

        for (auto i = index + count, j = index; i < this->mLength + count; ++i, ++j) {
            temp[i] = this->mString[j];
        }

        temp[this->mLength + count] = 0;
        delete[] this->mString;

        this->mString = new char[this->mLength + count + 1];
        this->mLength += count;
        this->mCapacity = this->mLength + 1;

        for (size_t i = 0; i < this->mLength + 1; ++i) {
            this->mString[i] = temp[i];
        }

        delete[] temp;
    }
}

void MyString::insert(size_t index, const char* string) {
    size_t length = 0;
    size_t i = 0;

    while (string[i++]) {
        ++length;
    }

    if (this->mCapacity - this->mLength > length) {
        auto temp = new char[this->mLength - index];

        for (i = index; i < this->mLength; ++i) {
            temp[i - index] = this->mString[i];
        }

        for (i = index; i < index + length; ++i) {
            this->mString[i] = string[i - index];
        }

        this->mLength += length;

        for (i = 0; i < this->mLength - index; ++i) {
            this->mString[i + index + length] = temp[i];
        }

        this->mString[this->mLength] = 0;

        delete[] temp;
    }
    else {
        char* temp = new char[this->mLength + length + 1];

        for (i = 0; i < index; ++i) {
            temp[i] = this->mString[i];
        }

        for (i = index; i < index + length; ++i) {
            temp[i] = string[i - index];
        }

        for (auto i = index + length, j = index; i < this->mLength + length; ++i, ++j) {
            temp[i] = this->mString[j];
        }

        temp[this->mLength + length] = 0;
        delete[] this->mString;

        this->mString = new char[this->mLength + length + 1];
        this->mLength += length;
        this->mCapacity = this->mLength + 1;

        for (size_t i = 0; i < this->mLength + 1; ++i) {
            this->mString[i] = temp[i];
        }

        delete[] temp;
    }
}

void MyString::insert(size_t index, const char* string, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        this->insert(index, 1, string[i]);
        ++index;
    }
}

void MyString::insert(size_t index, const std::string& string) {
    this->insert(index, string.c_str());
}

void MyString::insert(size_t index, std::string string, size_t count) {
    this->insert(index, string.c_str(), count);
}

void MyString::erase(size_t index, size_t count) {
    for (auto i = index; i < this->mLength - count; ++i) {
        this->mString[i] = this->mString[i + count];
    }

    this->mString[this->mLength - count] = 0;
    this->mLength -= count;
}

void MyString::append(size_t count, char character) {
    this->insert(this->length(), count, character);
}

void MyString::append(const char* string) {
    this->insert(this->length(), string);
}

void MyString::append(const char* string, size_t index, size_t count) {
    auto tmp = new char[count + 1];

    for (size_t i = index; i < index + count; ++i) {
        tmp[i - index] = string[i];
    }

    tmp[count] = 0;

    this->append(tmp);

    delete[] tmp;
}

void MyString::append(const std::string& string) {
    this->insert(this->length(), string);
}

void MyString::append(const std::string& string, size_t index, size_t count) {
    this->append(string.c_str(), index, count);
}

void MyString::replace(size_t index, size_t count, const char* string) {
    this->erase(index, count);
    this->insert(index, string);
}

void MyString::replace(size_t index, size_t count, const std::string& string) {
    this->replace(index, count, string.c_str());
}

MyString MyString::substr(size_t index) const {
    MyString string;

    string.append(this->mString, index, this->mLength - index);

    return string;
}

MyString MyString::substr(size_t index, size_t count) const {
    MyString string;

    string.append(this->mString, index, count);

    return string;
}

int MyString::find(const char* string) const {
    auto result = StrStr(this->mString, string);

    if (result == nullptr) {
        return -1;
    }

    return static_cast<int>(result - this->mString);
}

int MyString::find(const char* string, size_t index) const {
    auto tmp_string = this->substr(index);
    auto tmp = tmp_string.c_str();

    auto result = StrStr(tmp, string);

    if (result == nullptr) {
        return -1;
    }

    return static_cast<int>(result - tmp);
}

int MyString::find(const std::string& string) const {
    return this->find(string.c_str());
}

int MyString::find(const std::string& string, size_t index) const {
    return this->find(string.c_str(), index);
}

std::ostream& operator<<(std::ostream& out, MyString& string) {
    out << string.mString;

    return out;
}

std::istream& operator>>(std::istream& in, MyString& string) {
    char temp[1024] = { 0 };
    in.getline(temp, 1024);
    string = temp;

    return in;
}

int MyString::StrCmp(const char* str1, const char* str2) const {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

const char* MyString::StrStr(const char* string, const char* substring) const {
    while (*string) {
        auto start = string;
        auto sub = substring;

        while (*string && *sub && *string == *sub) {
            string++;
            sub++;
        }

        if (!*sub) {
            return start;
        }

        string = start + 1;
    }

    return nullptr;
}