#ifndef GOBJ_MESHFLIP_H
#define GOBJ_MESHFLIP_H

#include "types.h"

namespace gobj {

// TODO: size and members.
class MeshFlip {
public:
    void reset();
    void flip(u32 index);
};

}  // namespace gobj

#endif
