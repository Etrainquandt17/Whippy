#ifndef GOBJ_MODELDESC_H
#define GOBJ_MODELDESC_H

#include "hel/common/FixedString.h"
#include "types.h"

namespace gobj {

// TODO: members.
class ModelDesc {
public:
    ModelDesc();

    u32 _0[6];
    hel::common::FixedString<40> _18;
    u32 _40;
    u32 _44[5];
};

}  // namespace gobj

#endif
