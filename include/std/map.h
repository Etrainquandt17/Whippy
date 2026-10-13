#ifndef STD_MAP_H
#define STD_MAP_H

#include "std/tree.h"

namespace std {

template <class Key, class T, class Compare>
class __base_value_compare : private Compare {
public:
    typedef pair<const Key, T> value_type;

    __base_value_compare() {}
    __base_value_compare(const Compare& c) : Compare(c) {}

    bool operator()(const value_type& x, const value_type& y) const { return Compare::operator()(x.first, y.first); }
    bool operator()(const Key& x, const value_type& y) const { return Compare::operator()(x, y.first); }
    bool operator()(const value_type& x, const Key& y) const { return Compare::operator()(x.first, y); }
};

template <class T>
struct __map_can_transform {
    static const bool value = false;
};

template <class T>
struct __map_can_transform<T*> {
    static const bool value = true;
};

template <>
struct __map_can_transform<unsigned long> {
    static const bool value = true;
};

// Maps whose values are one word wide share a tree of unsigned long.
// TODO: the general form, with a tree of its own value type, is not written.
template <class Key, class T, class Compare, class Allocator, bool transform>
class __map_do_transform;

template <class Key, class T, class Compare, class Allocator>
class __map_do_transform<Key, T, Compare, Allocator, true> {
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const Key, T> value_type;
    typedef Compare key_compare;
    typedef typename Allocator::template rebind<value_type>::other allocator_type;

private:
    typedef pair<const Key, unsigned long> tree_value_type;
    typedef __base_value_compare<Key, unsigned long, Compare> tree_compare;
    typedef typename Allocator::template rebind<tree_value_type>::other tree_allocator_type;
    typedef __tree<tree_value_type, tree_compare, tree_allocator_type> tree_type;

public:
    class const_iterator {
    public:
        const_iterator() {}
        const_iterator(typename tree_type::const_iterator i) : i_(i) {}

        const value_type& operator*() const { return (const value_type&)*i_; }
        const value_type* operator->() const { return (const value_type*)i_.operator->(); }

        bool operator==(const const_iterator& other) const { return i_ == other.i_; }
        bool operator!=(const const_iterator& other) const { return i_ != other.i_; }

    private:
        typename tree_type::const_iterator i_;
    };

    typedef typename tree_type::iterator iterator;

    __map_do_transform(const Compare& comp, const Allocator& a) : tree_(tree_compare(comp), allocator_type(a)) {}

    iterator begin() { return tree_.begin(); }
    iterator end() { return tree_.end(); }
    const_iterator end() const { return tree_.end(); }
    const_iterator find(const key_type& x) const { return tree_.find(x); }

    pair<iterator, bool> insert(const value_type& x) { return tree_.insert_one((const tree_value_type&)x); }

private:
    tree_type tree_;
};

template <class Key, class T, class Compare, class Allocator>
class map : public __map_do_transform<Key, T, Compare, Allocator, __map_can_transform<T>::value> {
    typedef __map_do_transform<Key, T, Compare, Allocator, __map_can_transform<T>::value> base;

public:
    explicit map(const Compare& comp = Compare(), const Allocator& a = Allocator()) : base(comp, a) {}
};

}  // namespace std

#endif
