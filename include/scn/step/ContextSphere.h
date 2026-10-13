#ifndef SCN_STEP_CONTEXTSPHERE_H
#define SCN_STEP_CONTEXTSPHERE_H

#include "types.h"

namespace scn {
namespace step {

// TODO: members. It sits at 0x518 of Context.
class ContextSphere {
public:
    bool getIsGetCurrent(u32 index) const;
};

}
}

#endif
