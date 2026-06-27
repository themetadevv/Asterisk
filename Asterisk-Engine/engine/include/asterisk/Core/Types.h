#pragma once

#include <map>
#include <unordered_map>
#include <memory>

// containers

template <typename _Key, typename _Value>
using Map = std::map<_Key, _Value>;

template <typename _Key, typename _Value>
using UnorderedMap = std::unordered_map<_Key, _Value>;

template <typename T>
using Vector = std::vector<T>;

// memory

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr UniquePtr<T> CreateUnique(Args&&... args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr SharedPtr<T> CreateShared(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}