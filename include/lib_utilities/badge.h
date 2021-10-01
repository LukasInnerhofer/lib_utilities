#pragma once

namespace LibUtilities
{

template <typename T>
class Badge
{
public:
    friend T;

private:
    constexpr Badge() = default;

    Badge(Badge<T> const &) = delete;
    Badge &operator=(Badge<T> const &) = delete;

    Badge(Badge<T> &&) = delete;
    Badge &operator=(Badge<T> const &&) = delete;
};

}