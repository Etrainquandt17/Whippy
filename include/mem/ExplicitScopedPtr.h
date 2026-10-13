#ifndef MEM_EXPLICITSCOPEDPTR_H
#define MEM_EXPLICITSCOPEDPTR_H

#include "hel/common/NonCopyable.h"
#include "mem/IAllocator.h"
#include "types.h"

namespace mem {

class ExplicitScopedPtrUtil {
public:
    static void CheckPointerIsValid(const void* ptr);
};

// TODO: the bodies below and the base are the original's. They are expanded where a unit uses one once, and
// partly written units that call them would expand them, so they are opt-in until those are done.
#ifdef MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE
#define MEM_EXPLICITSCOPEDPTR_BASE : private hel::common::NonCopyable
#else
#define MEM_EXPLICITSCOPEDPTR_BASE
#endif

template <typename T>
class ExplicitScopedPtr MEM_EXPLICITSCOPEDPTR_BASE {
public:
    ExplicitScopedPtr() : _0(0), mPtr(0) {}
    // TODO: _0 is the allocator; it should be an IAllocator*.
    ExplicitScopedPtr(IAllocator& allocator) : _0(reinterpret_cast<u32>(&allocator)), mPtr(0) {}
#ifdef MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE
    ~ExplicitScopedPtr() { destruct(); }

    void destruct() {
        if (isConstruct()) {
            ref().~T();
            reinterpret_cast<IAllocator*>(_0)->allocatorFree(mPtr);
            mPtr = 0;
        }
    }

    bool isConstruct() const { return mPtr != 0; }
    T* operator->() const {
        ExplicitScopedPtrUtil::CheckPointerIsValid(mPtr);
        return mPtr;
    }
    T& ref() const {
        ExplicitScopedPtrUtil::CheckPointerIsValid(mPtr);
        return *mPtr;
    }
#else
    ~ExplicitScopedPtr();
    void destruct();
    bool isConstruct() const;
    T* operator->() const;
    T& ref() const;
#endif

    void construct() { mPtr = new (*reinterpret_cast<IAllocator*>(_0)) T(); }

    template <typename A1>
    void construct(A1 a1) {
        mPtr = new (*reinterpret_cast<IAllocator*>(_0)) T(a1);
    }

    template <typename A1, typename A2>
    void construct(A1 a1, A2 a2) {
        mPtr = new (*reinterpret_cast<IAllocator*>(_0)) T(a1, a2);
    }

    template <typename A1, typename A2, typename A3>
    void construct(A1 a1, A2 a2, A3 a3) {
        mPtr = new (*reinterpret_cast<IAllocator*>(_0)) T(a1, a2, a3);
    }

    template <typename U>
    void constructE() {
        constructIN(new (*reinterpret_cast<IAllocator*>(_0)) U());
    }

    template <typename U, typename A1>
    void constructE(A1 a1) {
        constructIN(new (*reinterpret_cast<IAllocator*>(_0)) U(a1));
    }

    template <typename U, typename A1, typename A2>
    void constructE(A1 a1, A2 a2) {
        constructIN(new (*reinterpret_cast<IAllocator*>(_0)) U(a1, a2));
    }

    template <typename U, typename A1, typename A2, typename A3>
    void constructE(A1 a1, A2 a2, A3 a3) {
        constructIN(new (*reinterpret_cast<IAllocator*>(_0)) U(a1, a2, a3));
    }

    void constructIN(T* ptr) { mPtr = ptr; }

    // TODO: name. The gimmick managers test the pointer in place where isConstruct() would be a call.
    T* get() const { return mPtr; }

private:
    u32 _0;
    T* mPtr;
};

}  // namespace mem

#endif
