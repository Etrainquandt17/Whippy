#ifndef SCN_STEP_ENEMY_SIGNAL_H
#define SCN_STEP_ENEMY_SIGNAL_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Signal {
public:
    Signal();

    void clear();
    bool isValid() const;
    void set(u32 signal);
    u32 get() const;

private:
    u32 mSignal;
};

}
}
}

#endif
