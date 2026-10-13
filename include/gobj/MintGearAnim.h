#ifndef GOBJ_MINTGEARANIM_H
#define GOBJ_MINTGEARANIM_H

#include "gobj/GearAnim.h"
#include "types.h"

namespace gobj {

// What a script holds as a "GObj.GearAnim".
class MintGearAnim {
public:
    static MintGearAnim Obj();
    static void RegisterForce(GearAnim& obj);
    static void Unregister();
    static void Start(u32 index);
    static void Start(u32 index, bool loop);
    static void Start(u32 index, bool loop, u32 arg);
    static f32 Frame();
    static int TotalFrame();
    static void SetFrame(f32 frame);
    static bool IsAnimEnd();
    static bool IsLooped();
    static f32 FrameRate();
    static void SetFrameRate(f32 rate);
    static int CurrentG3DAnimIndex();

    void start(u32 index) const { mObj->start(index); }
    void start(u32 index, bool loop) const { mObj->start(index, loop); }
    void start(u32 index, bool loop, u32 arg) const { mObj->start(index, loop, arg); }
    f32 frame() const { return mObj->frame(); }
    f32 totalFrame() const { return mObj->totalFrame(); }
    void setFrame(f32 frame) { mObj->setFrame(frame); }
    bool isAnimEnd() const { return mObj->isAnimEnd(); }
    bool isLooped() const { return mObj->isLooped(); }
    f32 frameRate() const { return mObj->frameRate(); }
    void setFrameRate(f32 rate) const { mObj->setFrameRate(rate); }
    int currentG3DAnimIndex() const { return mObj->currentG3DAnimIndex(); }

private:
    GearAnim* mObj;
};

}  // namespace gobj

#endif
