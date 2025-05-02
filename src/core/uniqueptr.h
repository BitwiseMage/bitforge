#pragma once

#include "tracing.h"

inline void* operator new(size_t size)
{
    BIT_TRACING;
    if (size == 0)
    {
        return nullptr;
    }

    void* pointer = std::malloc(size);
    if (!pointer)
    {
        return nullptr;
    }

    BIT_MEM_TRACING_ALLOC(pointer, size);
    return pointer;
}

inline void operator delete(void* pointer)
{
    BIT_TRACING;
    BIT_MEM_TRACING_FREE(pointer);
    std::free(pointer);
}

template<class T>
class UniquePtr
{
public:
    UniquePtr() = default;
    UniquePtr(const UniquePtr&) = delete;
    ~UniquePtr() { Clean(); }

    explicit UniquePtr(T* ptr) : m_ptr(ptr) { }
    UniquePtr(UniquePtr&& other) noexcept : m_ptr(other.Release()) { }

    template<class U, typename = typename std::enable_if<std::is_convertible<U*, T*>::value>::type>
    explicit UniquePtr(UniquePtr<U>&& other) noexcept : m_ptr(other.Release()) { }

    T& operator*() const { return *m_ptr; }
    T* operator->() const noexcept { return m_ptr; }
    explicit operator bool() const noexcept { return m_ptr != nullptr; }

    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
        Clean();
        m_ptr = other.Release();
        return *this;
    }

    T* GetRawPtr() const { return m_ptr; }

    void Acquire(T* ptr)
    {
        Clean();
        m_ptr = ptr;
    }

    T* Release()
    {
        T* ptr = m_ptr;
        m_ptr = nullptr;
        return ptr;
    }

    void Clean()
    {
        if (!m_ptr)
        {
            return;
        }

        delete m_ptr;
        m_ptr = nullptr;
    }

private:
    T* m_ptr = nullptr;
};

template<typename T, typename... Args>
UniquePtr<T> MakeUniquePtr(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
