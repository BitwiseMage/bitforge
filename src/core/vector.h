#pragma once
#include "uniqueptr.h"
#include "logging/logger.h"

template <typename T>
class Vector
{
public:
    Vector() = default;
    Vector(const Vector&) = delete;

    explicit Vector(size_t capacity_initial, const size_t capacity_limit_max = 0)
    {
        BIT_TRACING;
        if (capacity_initial == 0)
        {
            return;
        }

        if (capacity_limit_max && capacity_initial > capacity_limit_max)
        {
            BIT_LOG_WARNING("Clamping vector initial capacity to its max capacity limit");
            capacity_initial = capacity_limit_max;
        }

        T* data_ptr = new T[capacity_initial];
        if (!data_ptr)
        {
            BIT_LOG_ERROR("Vector memory allocation failed on creation");
            return;
        }

        m_data_ptr = data_ptr;
        m_capacity = capacity_initial;
        m_capacity_limit_max = capacity_limit_max;
    }

    T* PushBack(const T& new_value)
    {
        BIT_TRACING;
        if (m_size >= m_capacity)
        {
            if (m_capacity_limit_max > 0 && m_size >= m_capacity_limit_max)
            {
                BIT_LOG_ERROR("Pushing to vector failed due to max capacity being reached");
                return nullptr;
            }

            const size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            if (!Resize(new_capacity))
            {
                BIT_LOG_ERROR("Vector resizing failed");
                return nullptr;
            }
        }

        m_data_ptr.GetRawPtr()[m_size] = new_value;
        return m_data_ptr.GetRawPtr()[m_size++];
    }

    ~Vector()
    {
        m_data_ptr = nullptr;
        m_size = 0;
        m_capacity = 0;
        m_capacity_limit_max = 0;
    }

    T* GetData() { return m_data_ptr.GetRawPtr(); }

    T& operator[](size_t index) { return m_data_ptr.GetRawPtr()[index]; }
    const T& operator[](size_t index) const { return m_data_ptr.GetRawPtr()[index]; }
    Vector& operator=(const Vector& other)
    {
        BIT_TRACING;
        if (this == &other)
        {
            return *this;
        }

        T* new_data_ptr = new T[other.m_capacity];
        if (!new_data_ptr)
        {
            BIT_LOG_ERROR("Vector memory allocation failed during assignment");
            return *this;
        }

        m_data_ptr = nullptr;
        memcpy(new_data_ptr, other.m_data_ptr.GetRawPtr(), other.m_size * sizeof(T));

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        return *this;
    }

private:
    void OverrideSize(const size_t new_size) { m_size = new_size; }

    bool Resize(size_t new_capacity)
    {
        BIT_TRACING;

        if (m_capacity_limit_max && new_capacity > m_capacity_limit_max)
        {
            BIT_LOG_WARNING("Vector resize attempt to a size bigger than max capacity, clamping it");
            new_capacity = m_capacity_limit_max;
        }

        if (new_capacity <= m_capacity)
        {
            BIT_LOG_WARNING("Won't resize vector to a size smaller or equal to the current capacity");
            return false;
        }

        T* new_data_ptr = new T[new_capacity];
        if (!new_data_ptr)
        {
            BIT_LOG_ERROR("Vector memory allocation failed during resize");
            return false;
        }

        T* current_ptr = m_data_ptr.GetRawPtr();
        for (size_t i = 0; i < m_size; i++)
        {
            new_data_ptr[i] = std::move(current_ptr[i]);
        }

        m_data_ptr = nullptr;
        m_capacity = new_capacity;
        return true;
    }

    UniquePtr<T> m_data_ptr;

    size_t m_size = 0;
    size_t m_capacity = 0;
    size_t m_capacity_limit_max = 0;

    friend class String;
};
