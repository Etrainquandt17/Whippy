#ifndef UTIL_DISABLEINTERRUPTS_H
#define UTIL_DISABLEINTERRUPTS_H

#include "revolution/os/OSInterrupt.h"

namespace util {

class DisableInterrupts {
public:
    DisableInterrupts() : mEnabled(OSDisableInterrupts()) {}
    ~DisableInterrupts();

private:
    bool mEnabled;
};

}

#endif
