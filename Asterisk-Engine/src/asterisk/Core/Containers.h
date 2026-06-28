#pragma once

#include <map>
#include <unordered_map>

// containers

template <typename _Key, typename _Value>
using Map = std::map<_Key, _Value>;

template <typename _Key, typename _Value>
using UnorderedMap = std::unordered_map<_Key, _Value>;

template <typename T>
using Vector = std::vector<T>;