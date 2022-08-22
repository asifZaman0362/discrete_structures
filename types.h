#ifndef DISCREET_STRCTRS_TYPES_H
#define DISCREET_STRCTRS_TYPES_H

#include <utility>
#include <vector>
#include <ostream>

template <typename T>
class Set {
    private:
        std::vector<T> collection;
    public:
        Set() noexcept = default;
        Set(const Set<T>&) noexcept;
        Set(const std::vector<T>&) noexcept;
        Set(std::vector<T>&&) noexcept;
        Set(Set<T>&&) noexcept;
        bool Insert(const T&) noexcept;
        bool Remove(const T&) noexcept;
        const std::size_t Cardinality() const noexcept;
        const std::vector<T>& AsCollection() const noexcept;
        const Set<Set<T>> PowerSet() const noexcept;
        const Set<T> Difference(const Set<T>&) const noexcept;
        const Set<T> Union(const Set<T>&) const noexcept;
        const Set<T> Intersection(const Set<T>&) const noexcept;
        const Set<std::pair<T, T>> CrossProduct(const Set<T>&) const noexcept;
        const bool operator==(const Set<T>&);
        const bool operator!=(const Set<T>&);
};

template <typename T>
std::ostream operator<<(std::ostream&, const Set<T>&);

#endif
