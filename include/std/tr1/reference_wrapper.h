#ifndef STD_TR1_REFERENCE_WRAPPER_H
#define STD_TR1_REFERENCE_WRAPPER_H

namespace std {
namespace tr1 {

template <class T>
class reference_wrapper {
public:
    explicit reference_wrapper(T& t) : t_(&t) {}

    operator T&() const { return *t_; }
    T& get() const { return *t_; }

private:
    T* t_;
};

template <class T>
inline reference_wrapper<T> ref(T& t) {
    return reference_wrapper<T>(t);
}

template <class T>
inline reference_wrapper<const T> cref(const T& t) {
    return reference_wrapper<const T>(t);
}

}}  // namespace std::tr1

#endif
