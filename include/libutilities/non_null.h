#pragma once

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "libutilities/concepts.h"

namespace LibUtilities
{

template <typename T>
class NonNull
{
public:
    template <typename TOther>
    friend class NonNull;

    NonNull() = delete;
    NonNull(NonNull<T> const &rhs) :
        m_object{rhs.m_object}
    {
        validate();
    }
    NonNull(NonNull<T> &&rhs) :
        m_object{std::move(rhs.m_object)}
    {
        validate();
    }
    template <typename TOther>
    NonNull(NonNull<TOther> const &rhs) :
        m_object{rhs.m_object}
    {
        validate();
    }
    template <typename TOther>
    NonNull(NonNull<TOther> &&rhs) :
        m_object{std::move(rhs.m_object)}
    {
        validate();
    }
    NonNull(T &&rhs) :
        m_object{std::forward<T>(rhs)}
    {
        validate();
    }
    template <Constructible TOther>
    NonNull(TOther &&rhs) :
        m_object{std::forward<TOther>(rhs)}
    {
        validate();
    }

    NonNull<T> &operator=(NonNull<T> const &rhs)
    {
        m_object = rhs.m_object;
        return *this;
    }
    NonNull<T> &operator=(NonNull<T> &&rhs)
    {
        m_object = std::move(rhs.m_object);
        return *this;
    }
    template <typename TOther>
    NonNull<T> &operator=(NonNull<TOther> const &rhs)
    {
        m_object = rhs.m_object;
        return *this;
    }
    template <typename TOther>
    NonNull<T> &operator=(NonNull<TOther> &&rhs)
    {
        m_object = std::move(rhs.m_object);
        return *this;
    }
    NonNull<T> &operator=(T &&rhs)
    {
        m_object = std::forward<T>(rhs);
        return *this;
    }
    template <std::convertible_to<T> TOther>
    NonNull<T> &operator=(TOther &&rhs)
    {
        m_object = std::forward<TOther>(rhs);
        return *this;
    }

    operator T&()
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