#ifndef GOBJ_MINTTARGET_H
#define GOBJ_MINTTARGET_H

#include "types.h"

namespace gobj {

class Target;

namespace MintTarget {

void Register(Target& obj);
void Unregister(Target& obj);
bool IsRightDir();
void SetIsRightDir(bool isRightDir);
f32 GetSign();
void Invert();
void LoadDirection3();

}}  // namespace gobj::MintTarget

#endif
