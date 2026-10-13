#ifndef UTIL_DELEGATE_H
#define UTIL_DELEGATE_H

#include "mem/GlobalNewDeleteChanger.h"
#include "mem/IAllocator.h"
#include "std/tr1/function.h"
#include "types.h"
#include "util/PlacementNew.h"

namespace util {

namespace detail {

template <class F>
struct DelegateResult;

template <class R>
struct DelegateResult<R()> {
    typedef R Type;
};

}

// A std::tr1::function that keeps what it allocates in a buffer of its own.
template <class F, int N>
class Delegate {
public:
    class DelegateHeap : public mem::IAllocator {
    public:
        DelegateHeap() : mBuffer() {}
        virtual ~DelegateHeap() {}
        virtual void* allocatorAlloc(u32, s32) { return mBuffer; }
        virtual void allocatorFree(void*) {}

    private:
        u8 mBuffer[N];
    };

    Delegate() { mHeap.construct(); }
    Delegate(const Delegate& other) {
        mHeap.construct();
        *this = other;
    }
    Delegate(const std::tr1::function<F>& function) {
        mHeap.construct();
        *this = function;
    }
    ~Delegate() {
        {
            mem::GlobalNewDeleteChanger changer(*mHeap);
            mFunction = 0;
        }
        mHeap.destruct();
    }

    Delegate& operator=(const Delegate& other) { return *this = other.mFunction; }
    Delegate& operator=(const std::tr1::function<F>& function) {
        mem::GlobalNewDeleteChanger changer(*mHeap);
        mFunction = function;
        return *this;
    }

    // TODO: name. Only seen inlined, in util::IntervalTimer::update.
    bool isValid() const { return mFunction; }
    // The original's conversion (scn/subgame/common/event/Listener.cpp emits it). Opt-in, so that no unit written
    // without it converts where it did not before.
#ifdef UTIL_DELEGATE_OPERATOR_BOOL
    operator bool() const { return mFunction; }
#endif

    typename detail::DelegateResult<F>::Type operator()() const { return mFunction(); }

private:
    PlacementNew<DelegateHeap> mHeap;
    std::tr1::function<F> mFunction;
};

}  // namespace util

#endif
