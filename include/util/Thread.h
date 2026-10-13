#ifndef UTIL_THREAD_H
#define UTIL_THREAD_H

#include "hel/common/NonCopyable.h"
#include "mem/DataBlock.h"
#include "revolution/os/OSThread.h"
#include "types.h"

namespace util {

class Thread : private hel::common::NonCopyable {
public:
    static s32 GetCurrentThreadPriority();

    Thread(mem::IAllocator& allocator, u32 stackSize, s32 priority, OSThreadFunc func, void* arg);
    ~Thread();

private:
    mem::DataBlock mStack;
    OSThread mThread;
};

}

#endif
