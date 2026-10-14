#include "gobj/MintLocation.h"

#include "gobj/Location.h"
#include "hel/common/PointerWrapper.h"
#include "hel/mint/AddOnMathVector3.h"

using hel::common::PointerWrapper;
using hel::math::Vector3;

namespace gobj {

namespace {

PointerWrapper<Location> t_obj;

}

namespace MintLocation {

void Register(Location& obj) {
    t_obj.set(obj);
}

void Unregister(Location&) {
    t_obj.reset();
}

void LoadPos() {
    hel::mint::AddOnMathVector3::Set(t_obj->pos());
}

void LoadPrevPos() {
    hel::mint::AddOnMathVector3::Set(t_obj->prevPos());
}

const Vector3 Pos() {
    return t_obj->pos();
}

const Vector3 PrevPos() {
    return t_obj->prevPos();
}

}}  // namespace gobj::MintLocation
