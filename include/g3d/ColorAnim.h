#ifndef G3D_COLORANIM_H
#define G3D_COLORANIM_H

#include "g3d/ColorAnimContext.h"
#include "g3d/ColorAnimFlash.h"
#include "types.h"

namespace g3d {

// TODO: name the members.
class ColorAnim {
public:
    ColorAnim(const ColorAnimContext& context);

    void updateBegin();
    void updateFlash(const ColorAnimFlash& flash);
    void updateEnd();

private:
    u32 _0[0x70 / 4];
};

}  // namespace g3d

#endif
