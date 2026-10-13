#ifndef HEL_COMMON_SCOPEDPTR_H
#define HEL_COMMON_SCOPEDPTR_H

#include "hel/common/NonCopyable.h"

namespace hel {
namespace common {

class ScopedPtrUtil {
public:
    static void CheckPointerIsValid(const void* ptr);
};

template <typename T>
class ScopedPtr : private NonCopyable {
public:
    explicit ScopedPtr(T* ptr = 0);
    ~ScopedPtr() {
        T* ptr = mPtr;
        mPtr = 0;
        delete ptr;
    }

    // TODO: the body of the conversion; the one unit that converts calls it.
    typedef T* ScopedPtr::*BoolType;
    operator BoolType() const;

    T* operator->() const;
    T& operator*() const {
        ScopedPtrUtil::CheckPointerIsValid(mPtr);
        return *mPtr;
    }

    void swap(ScopedPtr& other) {
        T* ptr = other.mPtr;
        other.mPtr = mPtr;
        mPtr = ptr;
    }
    void reset(T* ptr = 0) { ScopedPtr(ptr).swap(*this); }

private:
    T* mPtr;
};

// TODO: the constructor has a body in the original, expanded where a unit builds one ScopedPtr and called where
// it builds several. Partly written units that call it would expand it, so the body is opt-in until they are done.
#ifdef HEL_COMMON_SCOPEDPTR_CONSTRUCTOR_INLINE
template <typename T>
ScopedPtr<T>::ScopedPtr(T* ptr) : mPtr(ptr) {}
#endif

}
}

#endif
