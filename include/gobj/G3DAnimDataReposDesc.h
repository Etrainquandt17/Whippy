#ifndef GOBJ_G3DANIMDATAREPOSDESC_H
#define GOBJ_G3DANIMDATAREPOSDESC_H

#include "types.h"

namespace gobj {

// TODO: members.
class G3DAnimDataReposDesc {
public:
    struct Entry {
        const char* mName;
        u32 _4;
    };

    // The implicit assignment is a function of its own in the original (supersword::SuperSword::setup calls it),
    // which an array member would not give.
    u32 _0;
    u32 _4;
    const Entry* _8;
};

}  // namespace gobj

#endif
