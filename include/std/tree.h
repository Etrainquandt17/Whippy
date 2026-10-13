#ifndef STD_TREE_H
#define STD_TREE_H

// The red-black tree under std::map, written to match the code the game was built with.
// TODO: only what mintvm uses: construction, insert_one, find and destruction.

#include "std/msl_utility.h"
#include "std/new.h"
#include "std/pair.h"

extern "C" {

struct __msl_file {
    unsigned long _0[0x14];
};

extern __msl_file __files[];

int fprintf(__msl_file* file, const char* format, ...);
void abort();

}

namespace std {

inline void __msl_error(const char* message) {
    fprintf(&__files[2], message);
    abort();
}

#pragma enumsalwaysint off
enum __tree_color {
    __tree_black,
    __tree_red
};
#pragma enumsalwaysint reset

// A pointer whose lowest bit holds a flag.
template <class T>
class __pointer_plus_bit {
public:
    __pointer_plus_bit(T p) : ptr_((unsigned long)p) {}

    __pointer_plus_bit& operator=(const __pointer_plus_bit& x) {
        ptr_ = (x.ptr_ & ~1UL) | (ptr_ & 1);
        return *this;
    }

    __pointer_plus_bit& operator=(T p) {
        ptr_ = (unsigned long)p | (ptr_ & 1);
        return *this;
    }

    operator T() const;
    T operator->() const { return (T)(ptr_ & ~1UL); }

    bool bit() const { return (bool)(ptr_ & 1); }

    void set_bit(bool b) {
        if (b) {
            ptr_ |= 1;
        } else {
            ptr_ &= ~1UL;
        }
    }

private:
    unsigned long ptr_;
};

// Below the class: a unit that keeps a copy of it has it behind its own functions (mint::Heap).
template <class T>
__pointer_plus_bit<T>::operator T() const {
    return (T)(ptr_ & ~1UL);
}

template <class VoidPtrAllocator>
struct __tree_node_base {
    typedef __tree_node_base* pointer;

    __tree_color color() const { return (__tree_color)parent_.bit(); }
    void set_color(__tree_color c) { parent_.set_bit(c); }

    pointer left_;
    pointer right_;
    __pointer_plus_bit<pointer> parent_;
};

template <class NodePtr>
class __red_black_tree {
public:
    static void balance_insert(NodePtr x, NodePtr& root) {
        x->set_color(__tree_red);
        while (x != root && x->parent_->color() == __tree_red) {
            if (x->parent_ == x->parent_->parent_->left_) {
                NodePtr y = x->parent_->parent_->right_;
                if (y != 0 && y->color() == __tree_red) {
                    x->parent_->set_color(__tree_black);
                    y->set_color(__tree_black);
                    x = x->parent_->parent_;
                    x->set_color(__tree_red);
                } else {
                    if (x == x->parent_->right_) {
                        x = x->parent_;
                        rotate_left(x, root);
                    }
                    x->parent_->set_color(__tree_black);
                    x->parent_->parent_->set_color(__tree_red);
                    rotate_right(x->parent_->parent_, root);
                }
            } else {
                NodePtr y = x->parent_->parent_->left_;
                if (y != 0 && y->color() == __tree_red) {
                    x->parent_->set_color(__tree_black);
                    y->set_color(__tree_black);
                    x = x->parent_->parent_;
                    x->set_color(__tree_red);
                } else {
                    if (x == x->parent_->left_) {
                        x = x->parent_;
                        rotate_right(x, root);
                    }
                    x->parent_->set_color(__tree_black);
                    x->parent_->parent_->set_color(__tree_red);
                    rotate_left(x->parent_->parent_, root);
                }
            }
        }
        root->set_color(__tree_black);
}


    static void rotate_left(NodePtr x, NodePtr& root) {
    NodePtr y = x->right_;
    if (root == x) {
        root = y;
    }
    x->right_ = y->left_;
    if (y->left_ != 0) {
        y->left_->parent_ = x;
    }
    y->parent_ = x->parent_;
    if (x == x->parent_->left_) {
        x->parent_->left_ = y;
    } else {
        x->parent_->right_ = y;
    }
    y->left_ = x;
    x->parent_ = y;
    }

    static void rotate_right(NodePtr x, NodePtr& root) {
    NodePtr y = x->left_;
    if (root == x) {
        root = y;
    }
    x->left_ = y->right_;
    if (y->right_ != 0) {
        y->right_->parent_ = x;
    }
    y->parent_ = x->parent_;
    if (x == x->parent_->left_) {
        x->parent_->left_ = y;
    } else {
        x->parent_->right_ = y;
    }
    y->right_ = x;
    x->parent_ = y;
    }

};

// Stands in for a node at the end of the tree: its left child is the root.
template <class Allocator>
struct __tree_anchor {
    typedef __tree_node_base<typename Allocator::template rebind<void*>::other> node_base;

    __tree_anchor() : left_(0) {}

    node_base* left_;
};

template <class T, class Compare, class Allocator>
class __tree_deleter {
public:
    typedef T value_type;
    typedef Compare value_compare;
    typedef Allocator allocator_type;
    typedef unsigned long size_type;
    typedef __tree_node_base<typename Allocator::template rebind<void*>::other> node_base;

    struct node : public node_base {
        value_type data_;
    };

    typedef typename Allocator::template rebind<node>::other node_allocator_type;
    typedef __tree_anchor<Allocator> anchor;

    template <bool is_const>
    class __generic_iterator {
    public:
        __generic_iterator() {}
        explicit __generic_iterator(const node_base* n) : ptr_(const_cast<node_base*>(n)) {}
        __generic_iterator(const __generic_iterator<false>& i) : ptr_(i.ptr_) {}

        value_type& operator*() const { return static_cast<node*>(ptr_)->data_; }
        value_type* operator->() const { return &static_cast<node*>(ptr_)->data_; }

        bool operator==(const __generic_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const __generic_iterator& other) const { return ptr_ != other.ptr_; }

        __generic_iterator& operator++() {
            if (ptr_->right_ != 0) {
                node_base* x = ptr_->right_;
                while (x->left_ != 0) {
                    x = x->left_;
                }
                ptr_ = x;
            } else {
                // TODO: the original takes the address of parent_ once per test and uses it for all three
                // reads; no plainer form gives that.
                __pointer_plus_bit<node_base*>* p;
                while (p = &ptr_->parent_, ptr_ != (*p)->left_) {
                    ptr_ = *p;
                }
                ptr_ = *p;
            }
            return *this;
        }

        node_base* ptr_;
    };

    typedef __generic_iterator<false> iterator;
    typedef __generic_iterator<true> const_iterator;

protected:
    __tree_deleter(const value_compare&, const allocator_type& a) : alloc_(a, 0), node_alloc_(a) {
        front_ = tail();
    }

    ~__tree_deleter();

    void destroy(node* n);

    size_type& sz() { return alloc_.second(); }
    node_allocator_type& node_alloc() { return node_alloc_.first(); }
    node_base* tail() { return (node_base*)&node_alloc_.second(); }
    const node_base* tail() const { return (const node_base*)&node_alloc_.second(); }
    node_base*& root() { return node_alloc_.second().left_; }
    node_base* const& root() const { return node_alloc_.second().left_; }

    Metrowerks::compressed_pair<allocator_type, size_type> alloc_;
    Metrowerks::compressed_pair<node_allocator_type, anchor> node_alloc_;
    node_base* front_;
};

template <class T, class Compare, class Allocator>
__tree_deleter<T, Compare, Allocator>::~__tree_deleter() {
    if (root() != 0) {
        destroy((node*)root());
    }
}

template <class T, class Compare, class Allocator>
void __tree_deleter<T, Compare, Allocator>::destroy(node* n) {
    if (n->left_ != 0) {
        destroy((node*)n->left_);
    }
    if (n->right_ != 0) {
        destroy((node*)n->right_);
    }
    n->data_.~value_type();
    node_alloc().deallocate(n, 1);
}

template <class T, class Compare, class Allocator>
class __tree_constructor : public __tree_deleter<T, Compare, Allocator> {
    typedef __tree_deleter<T, Compare, Allocator> base;

protected:
    __tree_constructor(const typename base::value_compare& comp, const typename base::allocator_type& a)
        : base(comp, a) {}
};

template <class T, class Compare, class Allocator>
class __tree : public __tree_constructor<T, Compare, Allocator> {
    typedef __tree_constructor<T, Compare, Allocator> base;

public:
    typedef typename base::value_type value_type;
    typedef typename base::value_compare value_compare;
    typedef typename base::allocator_type allocator_type;
    typedef typename base::size_type size_type;
    typedef typename base::node_base node_base;
    typedef typename base::node node;
    typedef typename base::node_allocator_type node_allocator_type;
    typedef typename base::iterator iterator;
    typedef typename base::const_iterator const_iterator;

    __tree(const value_compare& comp, const allocator_type& a) : base(comp, a) {}

    iterator begin() { return iterator(this->front_); }
    iterator end() { return iterator(this->tail()); }
    const_iterator end() const { return const_iterator(this->tail()); }
    size_type max_size() const { return 0xFFFFFFFF; }

    pair<iterator, bool> insert_one(const value_type& x) { return insert_unique(x); }

    template <class Key>
    const_iterator find(const Key& x) const {
        const node_base* result = lower_bound_node(x);
        if (result == this->tail() || value_compare()(x, ((const node*)result)->data_)) {
            result = this->tail();
        }
        return const_iterator(result);
    }

private:
    template <class Key>
    const node_base* lower_bound_node(const Key& x) const {
        const node_base* result = this->tail();
        const node* i = (const node*)this->root();
        while (i != 0) {
            if (!value_compare()(i->data_, x)) {
                result = i;
                i = (const node*)i->left_;
            } else {
                i = (const node*)i->right_;
            }
        }
        return result;
    }

    // The library's own names for these two are not known. They are not inline,
    // which is what puts the functions they use at the end of a unit.
    pair<iterator, bool> insert_unique(const value_type& x);
    node* insert_node(const value_type& x, bool go_left, node_base* parent, bool leftmost);
};

template <class T, class Compare, class Allocator>
pair<typename __tree<T, Compare, Allocator>::iterator, bool> __tree<T, Compare, Allocator>::insert_unique(const value_type& x) {
    // The order of these declarations decides the registers; found with compare.py -p.
    node* prev;
    node* i;
    bool go_left;
    node_base* parent;
    bool leftmost;

    prev = 0;
    parent = this->tail();
    i = (node*)this->root();
    go_left = true;
    leftmost = true;
    while (i != 0) {
        parent = i;
        if (value_compare()(x, i->data_)) {
            i = (node*)i->left_;
            go_left = true;
        } else {
            prev = i;
            i = (node*)i->right_;
            go_left = false;
            leftmost = false;
        }
    }
    if (prev == 0 || value_compare()(prev->data_, x)) {
        return pair<iterator, bool>(iterator(insert_node(x, go_left, parent, leftmost)), true);
    }
    return pair<iterator, bool>(iterator(prev), false);
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::node* __tree<T, Compare, Allocator>::insert_node(const value_type& x, bool go_left, node_base* parent, bool leftmost) {
    if (this->sz() == max_size()) {
        __msl_error("tree::insert length error");
    }
    Metrowerks::alloc_ptr<node, node_allocator_type&> ap(this->node_alloc().allocate(1), this->node_alloc());
    new (&ap->data_) value_type(x);
    node* n = ap.release();
    n->left_ = n->right_ = 0;
    new (&n->parent_) __pointer_plus_bit<node_base*>(parent);
    if (go_left) {
        parent->left_ = n;
    } else {
        parent->right_ = n;
    }
    ++this->sz();
    node_base* root = this->root();
    __red_black_tree<node_base*>::balance_insert(n, root);
    if (leftmost) {
        this->front_ = n;
    }
    return n;
}

}  // namespace std

#endif
