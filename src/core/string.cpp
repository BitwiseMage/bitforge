#include "string.h"

String::String(const char* str_ptr)
{
    ImportFromCharPtr(str_ptr);
}

String::String(const String& src_string)
{
    m_data = src_string.m_data;
}

void String::ImportFromCharPtr(const char* str_ptr)
{
    BIT_TRACING;
    if (!str_ptr)
    {
        BIT_LOG_ERROR("String import from char pointer failed due to the provided nullptr");
        return;
    }

    if (m_data.GetData() == str_ptr)
    {
        BIT_LOG_ERROR("String import from char pointer failed due to the existing string already having the same pointer");
        return;
    }

    size_t string_size = 0;
    const char* ptr_c = str_ptr;
    while (*ptr_c)
    {
        ++string_size;
        ++ptr_c;
    }

    if (string_size == 0)
    {
        BIT_LOG_ERROR("String import from char pointer failed due to 0 sized source string");
        return;
    }


    m_data = Vector<char>(++string_size);
    std::memcpy(m_data.GetData(), str_ptr, string_size);
    m_data.OverrideSize(string_size);
}


String& String::operator=(const char* str_ptr)
{
    BIT_TRACING;
    ImportFromCharPtr(str_ptr);
    return *this;
}

String& String::operator=(const String& other)
{
    BIT_TRACING;
    m_data = other.m_data;
    return *this;
}
