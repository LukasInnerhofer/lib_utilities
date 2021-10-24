#pragma once

#include <memory>
#include <stdexcept>
#include <utility>

namespace LibUtilities
{

template <typename T>
class NonNull
{
public:
    NonNull() = delete;
    NonNull(auto... args) :
        m_object{args...}
    {
        validate();
    }

    operator T() const
    {
        return m_object;
    }

    decltype(*std::declval<T>()) operator*() const
    {
        return *m_object;
    }

    decltype(std::declval<T>().operator->()) operator->() const
    {
        return m_object.operator->();
    }

private:
    void validate()
    {
        if (m_object == nullptr)
        {
            throw std::invalid_argument("LibUtilities::NonNull Error. Object must be non null.");
        }
    }

    T m_object;
};

template <typename T>
using NonNullSharedPtr = NonNull<std::shared_ptr<T>>;
template <typename T>
using NonNullUniquePtr = NonNull<std::unique_ptr<T>>;

}

using LibUtilities::NonNullSharedPtr;
using LibUtilities::NonNullUniquePtr;