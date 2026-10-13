#ifndef GOBJ_GEARANIM_H
#define GOBJ_GEARANIM_H

#include "types.h"

namespace gobj {

class MintGearAnim;

// TODO: members. The first three words are the animation table (two counts and the entries).
struct GearAnimDesc {
    u32 _0;
    u32 _4;
    const void* _8;
    u32 _C;
};

class GearAnim {
public:
    void clear();
    void start(u32 index);
    void start(u32 index, bool loop);
    void start(u32 index, bool loop, u32 arg);
    bool isAnimEnd() const;
    bool isLooped() const;
    f32 frame() const;
    int totalFrame() const;
    void setFrame(f32 frame);
    void setFrameToTail();
    f32 frameRate() const;
    void setFrameRate(f32 rate);
    int currentG3DAnimIndex() const;
    MintGearAnim mint();
};

}

#endif
