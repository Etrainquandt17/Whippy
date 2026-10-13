#ifndef NW4R_UT_LOCK_H
#define NW4R_UT_LOCK_H
#include <key/nw4r/types_nw4r.h>

#include <key/nw4r/ut/ut_NonCopyable.h>

#include <key/revolution/OS.h>

namespace nw4r {
namespace ut {
namespace detail {

/******************************************************************************
 *
 * Mutex lock functions
 *
 ******************************************************************************/
inline void Lock(OSMutex& rMutex) {
    OSLockMutex(&rMutex);
}
inline void Unlock(OSMutex& rMutex) {
    OSUnlockMutex(&rMutex);
}

/******************************************************************************
 *
 * AutoLock
 *
 ******************************************************************************/
template <typename T> class AutoLock : private NonCopyable {
public:
    explicit AutoLock(T& rLockObj) : mLockObj(rLockObj) {
        Lock(mLockObj);
    }
    ~AutoLock() {
        Unlock(mLockObj);
    }

private:
    T& mLockObj; // at 0x0
};

} // namespace detail

/******************************************************************************
 *
 * AutoInterruptLock
 *
 ******************************************************************************/
class AutoInterruptLock : private NonCopyable {
public:
    AutoInterruptLock() : mOldState(OSDisableInterrupts()) {}
    ~AutoInterruptLock() {
        OSRestoreInterrupts(mOldState);
    }

private:
    BOOL mOldState; // at 0x0
};

} // namespace ut
} // namespace nw4r

#endif
