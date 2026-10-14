#include "gobj/MintGearAnim.h"

#include "hel/common/PointerWrapper.h"

using hel::common::PointerWrapper;

namespace gobj {

namespace {

PointerWrapper<GearAnim> t_obj;

}

MintGearAnim MintGearAnim::Obj() {
    return t_obj->mint();
}

void MintGearAnim::RegisterForce(GearAnim& obj) {
    t_obj.set(obj);
}

void MintGearAnim::Unregister() {
    t_obj.reset();
}

void MintGearAnim::Start(u32 index) {
    t_obj->start(index);
}

void MintGearAnim::Start(u32 index, bool loop) {
    t_obj->start(index, loop);
}

void MintGearAnim::Start(u32 index, bool loop, u32 arg) {
    t_obj->start(index, loop, arg);
}

f32 MintGearAnim::Frame() {
    return t_obj->frame();
}

int MintGearAnim::TotalFrame() {
    return t_obj->totalFrame();
}

void MintGearAnim::SetFrame(f32 frame) {
    t_obj->setFrame(frame);
}

bool MintGearAnim::IsAnimEnd() {
    return t_obj->isAnimEnd();
}

bool MintGearAnim::IsLooped() {
    return t_obj->isLooped();
}

f32 MintGearAnim::FrameRate() {
    return t_obj->frameRate();
}

void MintGearAnim::SetFrameRate(f32 rate) {
    t_obj->setFrameRate(rate);
}

int MintGearAnim::CurrentG3DAnimIndex() {
    return t_obj->currentG3DAnimIndex();
}

}  // namespace gobj
