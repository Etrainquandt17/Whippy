#ifndef SCN_STEP_CHARA_SHADOW_H
#define SCN_STEP_CHARA_SHADOW_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: members and the other functions.
class Shadow {
public:
    void update();
    void updateUseGPU();
    void setVisibility(bool isVisible);
    bool isVisible() const;
    void changeDepth(f32 depth);
    void changeMaxHeight(f32 height);
    void changeDiameter(f32 diameter);
    void changeColor(const GXColor& color);
};

}
}
}

#endif
