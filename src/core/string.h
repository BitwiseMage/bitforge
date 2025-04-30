#pragma once
#include "vector.h"

class String
{
public:
    String() = default;
    ~String() = default;

    char* GetCString() { return m_data.GetData(); }
    std::string ToStdString() { return std::string(m_data.GetData()); }

    explicit String(const char* str_ptr);
    String(const String& src_string);

    String& operator=(const char* str_ptr);
    String& operator=(const String& other);

private:
    void ImportFromCharPtr(const char* str_ptr);

    Vector<char> m_data;
};
