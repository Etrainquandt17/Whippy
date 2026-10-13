#ifndef GOBJ_MINTMODEL_H
#define GOBJ_MINTMODEL_H

#include "types.h"

namespace gobj {

class Model;

namespace MintModel {

void Register(Model& obj);
void Unregister(Model& obj);
void LoadNode(u32 index);
void SetScale(f32 x, f32 y, f32 z);

}}  // namespace gobj::MintModel

#endif
