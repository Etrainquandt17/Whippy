#ifndef UTIL_MUTEX_H
#define UTIL_MUTEX_H

#include "revolution/os/OSMutex.h"

namespace util {

class Mutex {
public:
    Mutex();

    void lock();
    void unlock();

private:
    OSMutex mMutex;
};

class ScopedMutex {
public:
    ScopedMutex(Mutex& mutex);
    ~ScopedMutex();

private:
    Mutex* mMutex;
};

}

#endif
