#ifndef GOBJ_MINTLOCATION_H
#define GOBJ_MINTLOCATION_H

#include "hel/math/Vector3.h"

namespace gobj {

class Location;

namespace MintLocation {

void Register(Location& obj);
void Unregister(Location& obj);
void LoadPos();
void LoadPrevPos();
const hel::math::Vector3 Pos();
const hel::math::Vector3 PrevPos();

}}  // namespace gobj::MintLocation

#endif
