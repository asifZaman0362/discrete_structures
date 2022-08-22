#include <iostream>
#include <utility>
#include <vector>
#include "types.h"

template <typename T>
Set<T>::Set(const Set<T>& other) noexcept {
    std::copy(
        other.collection.begin(),
        other.collection.end(),
        std::back_inserter(collection)
    );
}

template <typename T>
Set<T>::Set(Set<T>&& other) noexcept :
    collection(std::move(other.collection)) {}

template <typename T>
Set<T>::Set(std::vector<T>&& collection) noexcept :
    collection(std::move(collection)) {}

template <typename T>
Set<T>::Set(const std::vector<T>& collection) noexcept {
    std::copy(
        collection.begin(),
        collection.end(),
        std::back_inserter(this->collection)
    );
}

template <typename T>
bool Set<T>::Insert(const T& item) noexcept {
    if (std::find(
        collection.begin(),
        collection.end(),
        item
    ) != collection.end())
        return false;
    collection.push_back(item);
    return true;
}

template <typename T>
bool Set<T>::Remove(const T& item) noexcept {
    if (std::find(
        collection.begin(), collection.end(), item) != collection.end()) {
        collection.erase(item);
        return true;
    }
    else return false;
}

template <typename T>
const size_t Set<T>::Cardinality() const noexcept {
    return collection.size();
}

template <typename T>
const std::vector<T>& Set<T>::AsCollection() const noexcept {
    return collection;
}

template <typename T>
const Set<Set<T>> Set<T>::PowerSet() const noexcept {
    Set<Set<T>> power_set;
    std::vector<std::vector<T>> subsets = { {} };
    for (auto& item : collection) {
        const auto n = subsets.size();
        for (size_t i = 0; i < n; i++) {
            std::vector<int> subset = {};
            std::copy(subsets[i].begin(), subsets[i].end(), std::back_inserter(subset));
            subset.push_back(item);
            subsets.push_back(subset);
        }
    }
    for (auto& subset : subsets) {
        power_set.Insert(Set<T>(subset));
    }
    return power_set;
}

template <typename T>
const Set<T> Set<T>::Difference(const Set<T>& other) const noexcept {
    std::vector<T> filtered_collection;
    for (auto& item : collection) {
        if (std::find(other.collection.begin(), other.collection.end(), item) == other.collection.end()) {
            filtered_collection.push_back(item);
        }
    }
    return Set<T>(filtered_collection);
}

template <typename T>
const Set<T> Set<T>::Union(const Set<T>& other) const noexcept {
    Set<T> new_set(AsCollection());
    for (auto& item : other.collection) {
        new_set.Insert(item);
    }
    return new_set;
}

template <typename T>
const Set<T> Set<T>::Intersection(const Set<T>& other) const noexcept {
    std::vector<T> new_collection = {};
    for (auto& item : collection) {
        if (std::find(other.collection.begin(), other.collection.end(), item) != other.collection.end()) {
            new_collection.push_back(item);
        }
    }
    return Set<T>(new_collection);
}

template <typename T>
const Set<std::pair<T, T>> Set<T>::CrossProduct(const Set<T>& other) const noexcept {
    std::vector<std::pair<T, T>> new_collection;
    for (auto& item : collection) {
        for (auto& other_item : other.collection) {
            new_collection.push_back({ item, other_item });
        }
    }
    return Set<std::pair<T, T>>(new_collection);
}

template <typename T>
const bool Set<T>::operator==(const Set<T>& other) {
    if (other.Cardinality() != Cardinality()) return false;
    auto& bigger = other.Cardinality() > Cardinality() ? other.collection : collection;
    auto& smaller = other.Cardinality() < Cardinality() ? other.collection : collection;
    for (auto& item : bigger) {
        if (std::find(other.collection.begin(), other.collection.end(), item) == other.collection.end())
            return false;
    }
    return true;
}

template <typename T>
const bool Set<T>::operator!=(const Set<T>& other) {
    return !(*this == other);
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Set<T>& set) {
	if (set.Cardinality()) {
		stream << "{ ";
		auto collection = set.AsCollection();
		for (auto& item : collection) {
			stream << item;
			if (item != collection.back()) stream << ", ";
		}
		stream << " }";
	}
	else {
		stream << "phi";
	}
	return stream;
}

