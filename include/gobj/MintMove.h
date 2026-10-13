#ifndef GOBJ_MINTMOVE_H
#define GOBJ_MINTMOVE_H

#include "types.h"

namespace gobj {

class Move;

namespace MintMove {

void Register(Move& obj);
void Unregister(Move& obj);
f32 GetSpeedH();
f32 GetSpeedV();
f32 GetSpeedD();
void SetSpeedH(f32 speed);
void SetSpeedV(f32 speed);
void SetSpeedD(f32 speed);

}}  // namespace gobj::MintMove

#endif
