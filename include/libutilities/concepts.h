#pragma once

#include <type_traits>

template<typename T, typename ...TArgs>
concept Constructible = std::is_constructible_v<T, TArgs...>;