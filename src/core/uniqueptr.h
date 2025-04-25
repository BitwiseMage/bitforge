#pragma once

#include "tracing.h"

inline void* operator new(size_t size)
{
    BITFORGE_TRACING;
    if (size == 0)
    {
        return nullptr;
    }

    void* pointer = std::malloc(size);
    if (!pointer)
    {
        return nullptr;
    }

    BITFORGE_MEM_TRACING_ALLOC(pointer, size);
    return pointer;
}

inline void operator delete(void* pointer)
{
    BITFORGE_TRACING;
    BITFORGE_MEM_TRACING_FREE(pointer);
    std::free(pointer);
}

template<class T>
class UniquePtr
{
public:
    UniquePtr() = delete;
    UniquePtr(const UniquePtr&) = delete;

    explicit UniquePtr(T* ptr) : m_ptr(ptr) { }
    UniquePtr(UniquePtr&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }

    ~UniquePtr() { Clear(); }

    T& operator*() const { return *m_ptr; }
    T* operator->() const noexcept { return m_ptr; }
    explicit operator bool() const noexcept { return m_ptr != nullptr; }
    UniquePtr& operator=(const T* new_ptr)
    {
        Clear();
        m_ptr = new_ptr;
        return *this;
    }

    UniquePtr& operator=(const UniquePtr&) = delete;

private:
    void Clear()
    {
        if (!m_ptr)
        {
            return;
        }
        delete m_ptr;
    }

    T* m_ptr = nullptr;
};

template<typename T, typename... Args>
UniquePtr<T> MakeUniquePtr(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
