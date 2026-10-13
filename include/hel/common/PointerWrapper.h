#ifndef HEL_COMMON_POINTERWRAPPER_H
#define HEL_COMMON_POINTERWRAPPER_H

namespace hel {
namespace common {

template <typename T>
class PointerWrapper {
public:
    PointerWrapper();

    // TODO: the original calls this from every use in scn/step/hero/Piggyback.cpp; with the body here, below the
    // class or behind the last use it is expanded.
    void unset() { mPtr = 0; }
    void set(T& obj) { mPtr = &obj; }
    void reset() { mPtr = 0; }
    bool wasSet() const { return mPtr != 0; }

    T& ref() const { return *mPtr; }
    T* operator->() const { return mPtr; }

private:
    T* mPtr;
};

template <typename T>
PointerWrapper<T>::PointerWrapper()
    : mPtr(0) {}

}
}

#endif
