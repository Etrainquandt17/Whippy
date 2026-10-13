#ifndef GOBJ_ANIM_H
#define GOBJ_ANIM_H

#include "g3d/ModelAnimAccessor.h"
#include "types.h"

namespace g3d {
class ResFileAccessor;
}

namespace gobj {

class Anim {
public:
    void registerResFile(u32 id, const g3d::ResFileAccessor& resFile);
    void unregisterResFile(u32 id);
    void start(u32 index);
    void start(u32 index, bool loop);
    void start(u32 index, bool loop, f32 frame);
    bool isAnimEnd() const;
    bool isLooped() const;
    f32 frame() const;
    int totalFrame() const;
    void setFrame(f32 frame);
    void setFrameToHead();
    void setFrameToTail();
    f32 frameRate() const;
    void setFrameRate(f32 rate);
    u32 currentG3DAnimIndex() const;
    void subAnimSet(u32 slot, u32 index, u32 kind);
    void subAnimClear(u32 slot);
    void subAnimBindPartial(u32 slot, u32 node);
    g3d::ModelAnimAccessor subAnimAccessor(u32 slot);

private:
    u8 _0[0x2C];
};

}  // namespace gobj

#endif
