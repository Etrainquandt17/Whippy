#ifndef GOBJ_SCRIPT_H
#define GOBJ_SCRIPT_H

#include "types.h"

namespace gobj {

// TODO: size and members.
class Script {
public:
    u32 prevScriptIndex() const;
    u32 currentScriptIndex() const;
    void start(u32 index);
};

}

#endif
