#ifndef GOBJ_MINTANIM_H
#define GOBJ_MINTANIM_H

#include "types.h"

namespace gobj {

class Anim;

namespace MintAnim {

void Register(Anim& obj);
void Unregister(Anim& obj);
void Start(u32 index);
void Start(u32 index, bool loop);
void Start(u32 index, bool loop, f32 frame);
f32 Frame();
int TotalFrame();
void SetFrame(f32 frame);
void SetFrameToHead();
void SetFrameToTail();
bool IsAnimEnd();
bool IsLooped();
f32 FrameRate();
void SetFrameRate(f32 rate);
int CurrentG3DAnimIndex();
void CheckIsReachableFrame(u32 frame);

}
}

#endif
