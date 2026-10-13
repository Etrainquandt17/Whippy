#include "gobj/MintAnim.h"

#include "gobj/Anim.h"
#include "hel/common/PointerWrapper.h"

namespace gobj {

namespace {

hel::common::PointerWrapper<Anim> t_obj;

}

namespace MintAnim {

void Register(Anim& obj) {
    t_obj.set(obj);
}

void Unregister(Anim&) {
    t_obj.reset();
}

void Start(u32 index) {
    t_obj->start(index);
}

void Start(u32 index, bool loop) {
    t_obj->start(index, loop);
}

void Start(u32 index, bool loop, f32 frame) {
    t_obj->start(index, loop, frame);
}

f32 Frame() {
    return t_obj->frame();
}

int TotalFrame() {
    return t_obj->totalFrame();
}

void SetFrame(f32 frame) {
    t_obj->setFrame(frame);
}

void SetFrameToHead() {
    t_obj->setFrameToHead();
}

void SetFrameToTail() {
    t_obj->setFrameToTail();
}

bool IsAnimEnd() {
    return t_obj->isAnimEnd();
}

bool IsLooped() {
    return t_obj->isLooped();
}

f32 FrameRate() {
    return t_obj->frameRate();
}

void SetFrameRate(f32 rate) {
    t_obj->setFrameRate(rate);
}

int CurrentG3DAnimIndex() {
    return t_obj->currentG3DAnimIndex();
}

void CheckIsReachableFrame(u32) {}

}}  // namespace gobj::MintAnim
