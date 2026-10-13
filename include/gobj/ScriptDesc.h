#ifndef GOBJ_SCRIPTDESC_H
#define GOBJ_SCRIPTDESC_H

#include "types.h"

namespace gobj {

// TODO: members.
class ScriptDesc {
public:
    struct Entry {
        const char* mFunction;
        u32 _4;
        u32 _8;
        u32 _c;
        u32 _10;
    };

    u32 _0[3];
};

}  // namespace gobj

#endif
