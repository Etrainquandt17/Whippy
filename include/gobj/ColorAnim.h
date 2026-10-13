#ifndef GOBJ_COLORANIM_H
#define GOBJ_COLORANIM_H

#include "g3d/ColorAnimFlash.h"
#include "types.h"

namespace mem {

class IAllocator;

}

namespace gobj {

class IG3DModel;

// TODO: name the members.
struct ColorAnimDesc {
    ColorAnimDesc() : _0(0), _4(0) {}

    u32 _0;
    u32 _4;
};

// TODO: members.
class ColorAnim {
public:
    ColorAnim(const ColorAnimDesc& desc, mem::IAllocator& allocator, IG3DModel& model);
    ~ColorAnim();

    g3d::ColorAnimFlash flash() const;
    void setFlash(const g3d::ColorAnimFlash& flash);
    void updateUseGPU();

private:
    u32 _0[9];
};

}  // namespace gobj

#endif
