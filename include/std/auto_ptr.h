#ifndef STD_AUTO_PTR_H
#define STD_AUTO_PTR_H

namespace std {

template <typename Y>
struct auto_ptr_ref {
    Y* ptr_;
};

template <typename X>
class auto_ptr {
public:
    explicit auto_ptr(X* p = 0) : ptr_(p) {}
    auto_ptr(auto_ptr& a) : ptr_(a.release()) {}
    auto_ptr(auto_ptr_ref<X> r) : ptr_(r.ptr_) {}
    ~auto_ptr() { delete ptr_; }

    X& operator*() const { return *ptr_; }
    X* operator->() const { return ptr_; }
    X* get() const { return ptr_; }

    X* release() {
        X* tmp = ptr_;
        ptr_ = 0;
        return tmp;
    }

    void reset(X* p = 0) {
        if (ptr_ != p) {
            delete ptr_;
            ptr_ = p;
        }
    }

    template <typename Y>
    operator auto_ptr_ref<Y>() {
        auto_ptr_ref<Y> r;
        r.ptr_ = release();
        return r;
    }

private:
    X* ptr_;
};

}  // namespace std

#endif
